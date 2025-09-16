#pragma once
#include <Arduino.h>
// ---------- Pin definitions ----------
#define PIN_I2C_SDA 41
#define PIN_I2C_SCL 42

/* ---------- MPU-6500 registers ---------- */
static const uint8_t MPU_ADDR_68   = 0x68;   // AD0=0
static const uint8_t MPU_ADDR_69   = 0x69;   // AD0=1
static const uint8_t REG_WHO_AM_I  = 0x75;   // expect 0x70
static const uint8_t REG_PWR_MGMT1 = 0x6B;
static const uint8_t REG_SMPLRTDIV = 0x19;
static const uint8_t REG_CONFIG    = 0x1A;
static const uint8_t REG_GYRO_CFG  = 0x1B;   // we use ±250 dps
static const uint8_t REG_ACCEL_CFG = 0x1C;   // we use ±2 g
static const uint8_t REG_ACCEL_X_H = 0x3B;

/* ---------- scaling & math ---------- */
static const float ACCEL_LSB_PER_G   = 16384.0f;  // ±2g → 32768/2
static const float GYRO_LSB_PER_DPS  = 131.0f;    // ±250 dps → 32768/250
static const float G_IN_MS2          = 9.80665f;
static const float EMA_ALPHA         = 0.2f;      // smoothing (0..1)

/* ---------- structs ---------- */
struct ImuRaw {
    int16_t ax, ay, az;
    int16_t temp;
    int16_t gx, gy, gz;
};

/* ---------- globals (defined in .cpp) ---------- */
extern uint8_t mpuAddr;
extern float acc_bias_counts[3];
extern float gyr_bias_counts[3];

extern float ax_g_f, ay_g_f, az_g_f;
extern float gx_dps_f, gy_dps_f, gz_dps_f;

/* ---------- function prototypes ---------- */
bool i2cWrite8(uint8_t a, uint8_t r, uint8_t v);
bool i2cRead(uint8_t a, uint8_t r, uint8_t* b, size_t n);
bool i2cRead8(uint8_t a, uint8_t r, uint8_t& v);

bool mpuInit();
bool mpuReadRaw();
void IMU_Calibrate(uint16_t samples=200, uint16_t delay_ms=5);
void readAndPrintIMU();
