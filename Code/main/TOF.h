#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"

// --- Pin mapping ---
#define PIN_I2C_SDA 41
#define PIN_I2C_SCL 42
#define PIN_XSHUT   40

// --- Global sensor object ---
extern Adafruit_VL53L0X lox;

// --- Functions ---
bool vl53Init();
int  vl53ReadDistance();   // returns distance in mm, or -1 if fail
