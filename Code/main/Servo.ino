/*
 #include <ESP32Servo.h>

/* ---- Explicit LEDC (guaranteed 50 Hz) ---- */
/*
static const int SERVO_CH   = 0;   // LEDC channel 0..7 (or 0..15 on S3)
static const int SERVO_BITS = 16;  // 16-bit duty
static const int SERVO_HZ   = 50;  // 50 Hz

Servo myservo;
  int pos = 0;                // start position (0..180)
  bool centered = false;

inline uint32_t us_to_duty(int us) {
  // 20,000 us period at 50 Hz
  const uint32_t maxDuty = (1u << SERVO_BITS) - 1u;
  if (us < SERVO_MIN_PULSE_US) us = SERVO_MIN_PULSE_US;
  if (us > SERVO_MAX_PULSE_US) us = SERVO_MAX_PULSE_US;
  return (uint32_t)((us / 20000.0f) * (float)maxDuty);
}


void servoInit() {
  pinMode(PIN_SERVO, OUTPUT);              // be explicit
  ledcSetup(SERVO_CH, SERVO_HZ, SERVO_BITS);     // create a 50 Hz timer
  ledcAttachPin(PIN_SERVO, SERVO_CH);            // bind IO1 to that channel
  ledcWrite(SERVO_CH, us_to_duty(SERVO_CENTER_US)); // center on boot
  Serial.println("LEDC: 50 Hz attached to IO1");
}

void setServoAngle(int angle) {
  angle = constrain(angle, 0, 180);
  int pulse = map(angle, 0, 180, SERVO_MIN_PULSE_US, SERVO_MAX_PULSE_US);
  ledcWrite(SERVO_CH, us_to_duty(pulse));
}
*/



