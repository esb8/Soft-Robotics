#include "Magnet_Driver.h"

// Convert percentage (0–100) to duty-cycle value for ledcWrite
uint32_t pctToDuty(int pct) {
  pct = pct < 0 ? 0 : (pct > 100 ? 100 : pct);
  return (uint32_t)((((1 << PWM_BITS) - 1) * (uint32_t)pct) / 100);
}

// Hi-Z (fast release)
void hbridge_coast() {
  ledcWrite(PIN_INA, 0);
  ledcWrite(PIN_INB, 0);
}

// Brake (slow decay)
void hbridge_brake() {
  ledcWrite(PIN_INA, (1 << PWM_BITS) - 1);
  ledcWrite(PIN_INB, (1 << PWM_BITS) - 1);
}

// Drive OUT1 → OUT2
void drive_forward_pct(int duty_pct) {
  ledcWrite(PIN_INB, 0);
  ledcWrite(PIN_INA, pctToDuty(duty_pct));
}

// Drive OUT2 → OUT1
void drive_reverse_pct(int duty_pct) {
  ledcWrite(PIN_INA, 0);
  ledcWrite(PIN_INB, pctToDuty(duty_pct));
}
