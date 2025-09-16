#include "MPU6500.h"
#include <Wire.h>
#include <math.h>

#pragma once


/* ---------- globals ---------- */
uint8_t mpuAddr = MPU_ADDR_68; 
float acc_bias_counts[3] = {0,0,0};
float gyr_bias_counts[3] = {0,0,0};

float ax_g_f=0, ay_g_f=0, az_g_f=0;
float gx_dps_f=0, gy_dps_f=0, gz_dps_f=0;
// Write BYTE
bool i2cWrite8(uint8_t a, uint8_t r, uint8_t v) {
  Wire.beginTransmission(a); Wire.write(r); Wire.write(v);
  return Wire.endTransmission() == 0;
}
// Write n bit
bool i2cRead(uint8_t a, uint8_t r, uint8_t* b, size_t n) {
  Wire.beginTransmission(a); Wire.write(r);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom((int)a,(int)n) != (int)n) return false;
  for (size_t i=0;i<n;++i) b[i] = Wire.read();
  return true;
}
// read byte
bool i2cRead8(uint8_t a, uint8_t r, uint8_t& v) { return i2cRead(a,r,&v,1); }

bool mpuInit() {
  // probe 0x68 then 0x69
  uint8_t who=0; mpuAddr=MPU_ADDR_68;
  if (!i2cRead8(mpuAddr, REG_WHO_AM_I, who) || who != 0x70) {
    mpuAddr=MPU_ADDR_69; who=0; i2cRead8(mpuAddr, REG_WHO_AM_I, who);
  }
  Serial.printf("MPU WHO_AM_I at 0x%02X = 0x%02X (expect 0x70)\n", mpuAddr, who);
  if (who != 0x70) return false;

  // reset, wake, set ranges, ODR
  if (!i2cWrite8(mpuAddr, REG_PWR_MGMT1, 0x80)) return false; delay(100);
  if (!i2cWrite8(mpuAddr, REG_PWR_MGMT1, 0x01)) return false; // PLL, awake
  if (!i2cWrite8(mpuAddr, REG_SMPLRTDIV, 7))   return false;  // 1kHz/(7+1)=125 Hz
  if (!i2cWrite8(mpuAddr, REG_CONFIG, 3))      return false;  // DLPF ~44 Hz
  if (!i2cWrite8(mpuAddr, REG_GYRO_CFG, 0))    return false;  // ±250 dps
  if (!i2cWrite8(mpuAddr, REG_ACCEL_CFG, 0))   return false;  // ±2 g
  return true;
}

bool mpuReadRaw(ImuRaw &o) {
  uint8_t b[14];
  if (!i2cRead(mpuAddr, REG_ACCEL_X_H, b, sizeof(b))) return false;
  auto U=[](uint8_t h,uint8_t l){ return (int16_t)((h<<8)|l); };
  o.ax=U(b[0],b[1]); o.ay=U(b[2],b[3]); o.az=U(b[4],b[5]);
  o.temp=U(b[6],b[7]); o.gx=U(b[8],b[9]); o.gy=U(b[10],b[11]); o.gz=U(b[12],b[13]);
  return true;
}

/* ---------- Calibration (bias in COUNTS) ---------- */
void IMU_Calibrate(uint16_t samples, uint16_t delay_ms) {
  // assumes device is motionless and Z axis ~ +1 g
  long acc_sum[3] = {0,0,0};
  long gyr_sum[3] = {0,0,0};

  ImuRaw r;
  for (uint16_t i=0;i<samples;++i) {
    if (mpuReadRaw(r)) {
      acc_sum[0] += r.ax; acc_sum[1] += r.ay; acc_sum[2] += r.az;
      gyr_sum[0] += r.gx; gyr_sum[1] += r.gy; gyr_sum[2] += r.gz;
    }
    delay(delay_ms);
  }

  // average
  float acc_avg[3] = {
    acc_sum[0]/(float)samples,
    acc_sum[1]/(float)samples,
    acc_sum[2]/(float)samples
  };
  float gyr_avg[3] = {
    gyr_sum[0]/(float)samples,
    gyr_sum[1]/(float)samples,
    gyr_sum[2]/(float)samples
  };

  // accel bias: remove gravity from Z (assuming Z points up)
  acc_bias_counts[0] = acc_avg[0];
  acc_bias_counts[1] = acc_avg[1];
  acc_bias_counts[2] = acc_avg[2] - ACCEL_LSB_PER_G;  // subtract +1g

  // gyro bias: average is the bias in counts
  gyr_bias_counts[0] = gyr_avg[0];
  gyr_bias_counts[1] = gyr_avg[1];
  gyr_bias_counts[2] = gyr_avg[2];
}

void readAndPrintIMU() {
  ImuRaw r;
  if (!mpuReadRaw(r)) {
    Serial.println("IMU read failed");
    delay(100);
    return;
  }

  // Bias-correct in COUNTS
  float ax_c = (float)r.ax - acc_bias_counts[0];
  float ay_c = (float)r.ay - acc_bias_counts[1];
  float az_c = (float)r.az - acc_bias_counts[2];

  float gx_c = (float)r.gx - gyr_bias_counts[0];
  float gy_c = (float)r.gy - gyr_bias_counts[1];
  float gz_c = (float)r.gz - gyr_bias_counts[2];

  // Convert to g and dps
  float ax_g = ax_c / ACCEL_LSB_PER_G;
  float ay_g = ay_c / ACCEL_LSB_PER_G;
  float az_g = az_c / ACCEL_LSB_PER_G;

  float gx_dps_raw = gx_c / GYRO_LSB_PER_DPS;
  float gy_dps_raw = gy_c / GYRO_LSB_PER_DPS;
  float gz_dps_raw = gz_c / GYRO_LSB_PER_DPS;

  // Apply smoothing (EMA)
  ax_g_f = EMA_ALPHA * ax_g + (1.0f - EMA_ALPHA) * ax_g_f;
  ay_g_f = EMA_ALPHA * ay_g + (1.0f - EMA_ALPHA) * ay_g_f;
  az_g_f = EMA_ALPHA * az_g + (1.0f - EMA_ALPHA) * az_g_f;

  gx_dps_f = EMA_ALPHA * gx_dps_raw + (1.0f - EMA_ALPHA) * gx_dps_f;
  gy_dps_f = EMA_ALPHA * gy_dps_raw + (1.0f - EMA_ALPHA) * gy_dps_f;
  gz_dps_f = EMA_ALPHA * gz_dps_raw + (1.0f - EMA_ALPHA) * gz_dps_f;

  // Convert accel to m/s²
  float ax_ms2 = ax_g_f * G_IN_MS2;
  float ay_ms2 = ay_g_f * G_IN_MS2;
  float az_ms2 = az_g_f * G_IN_MS2;

  // Estimate pitch/roll from accel only
  float pitch_deg = atan2f(-ax_g_f, sqrtf(ay_g_f*ay_g_f + az_g_f*az_g_f)) * (180.0f / M_PI);
  float roll_deg  = atan2f( ay_g_f, az_g_f ) * (180.0f / M_PI);

  // Print
  Serial.printf("[IMU: Accel] (m/s²): X=%.2f Y=%.2f Z=%.2f\r\n", ax_ms2, ay_ms2, az_ms2);
  Serial.printf("[IMU: Gyro]  (°/s):  X=%.2f Y=%.2f Z=%.2f\r\n", gx_dps_f, gy_dps_f, gz_dps_f);
  Serial.printf("[IMU: Angles] (deg): Pitch=%.2f Roll=%.2f\r\n", pitch_deg, roll_deg);
}





