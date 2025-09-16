#include "MPU6500.h"
#include "Magnet_Driver.h"
#include <Arduino.h>
#include <Wire.h>
#include <math.h>
 
/* ---------- Pins (GPIO numbers) ---------- */
#define PIN_Servo_PWM 1

  void setup() {
    Serial.begin(115200);
// IMU 
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL, 100000);
    Serial.printf("Calibrating IMU... keep board still for ~1s\r\n");
    void IMU_Calibrate(uint16_t samples, uint16_t delay_ms);

    Serial.printf("Accel bias (cts): [%.1f, %.1f, %.1f], Gyro bias (cts): [%.1f, %.1f, %.1f]\r\n",
        acc_bias_counts[0], acc_bias_counts[1], acc_bias_counts[2],   
        gyr_bias_counts[0], gyr_bias_counts[1], gyr_bias_counts[2]);
  delay(50);
// Magnet Driver 
#if (PIN_NSLEEP >= 0)
  pinMode(PIN_NSLEEP, OUTPUT);
  digitalWrite(PIN_NSLEEP, LOW);
  delay(2);
  digitalWrite(PIN_NSLEEP, HIGH);
  delay(5);
#endif

  ledcAttach(PIN_INA, PWM_FREQ, PWM_BITS);
  ledcAttach(PIN_INB, PWM_FREQ, PWM_BITS);

  hbridge_coast();
  Serial.println("Magnet Driver ready.");
}

  void loop() {
  readAndPrintIMU();
  delay(300);
}

