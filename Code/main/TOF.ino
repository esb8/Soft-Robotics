#include "TOF.h"

// Global sensor instance
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

bool vl53Init() {
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL, 100000);  // 100 kHz
  if (!lox.begin()) {
    Serial.println("Failed to boot VL53L0X sensor!");
    return false;
  }
  Serial.println("VL53L0X sensor ready.");
  return true;
}

int vl53ReadDistance() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);  // false = no debug output

  if (measure.RangeStatus != 4) { // 4 = out of range
    return measure.RangeMilliMeter;
  } else {
    return -1; // invalid
  }
}
