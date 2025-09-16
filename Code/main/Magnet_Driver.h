#pragma once
#include <Arduino.h>

// ---------- Pin definitions ----------
#define PIN_INA    38   // DRV8874 INA (IN1)  -> PWM
#define PIN_INB    47   // DRV8874 INB (IN2)  -> PWM
#define PIN_NSLEEP -1   // set to your nSLEEP pin, or -1 if tied HIGH on PCB

// ---------- PWM settings ----------
const uint32_t PWM_FREQ = 20000;   // 20 kHz
const uint8_t  PWM_BITS = 10;      // 10-bit resolution (0..1023)

// ---------- API prototypes ----------
uint32_t pctToDuty(int pct);

void hbridge_coast();
void hbridge_brake();
void drive_forward_pct(int duty_pct);
void drive_reverse_pct(int duty_pct);
