// Motor A: IN1=19, IN2=21
// Motor B: IN3=23, IN4=22

// assign PWM channels
#define CH_A1 0
#define CH_A2 1
#define CH_B1 2
#define CH_B2 3

void setupMotors() {
  // setup PWM for all 4 IN pins
  ledcSetup(CH_A1, 5000, 8);  ledcAttachPin(19, CH_A1);
  ledcSetup(CH_A2, 5000, 8);  ledcAttachPin(21, CH_A2);
  ledcSetup(CH_B1, 5000, 8);  ledcAttachPin(23, CH_B1);
  ledcSetup(CH_B2, 5000, 8);  ledcAttachPin(22, CH_B2);
}

// Motor A forward/backward
void motorAForward(int speed) {
  ledcWrite(CH_A1, constrain(speed,0,255)); // PWM on IN1
  ledcWrite(CH_A2, 0);                      // IN2 LOW
}

void motorABackward(int speed) {
  ledcWrite(CH_A1, 0);
  ledcWrite(CH_A2, constrain(speed,0,255));
}

void motorAStop() {
  ledcWrite(CH_A1, 0);
  ledcWrite(CH_A2, 0);
}

// Motor B forward/backward
void motorBForward(int speed) {
  ledcWrite(CH_B1, constrain(speed,0,255));
  ledcWrite(CH_B2, 0);
}

void motorBBackward(int speed) {
  ledcWrite(CH_B1, 0);
  ledcWrite(CH_B2, constrain(speed,0,255));
}

void motorBStop() {
  ledcWrite(CH_B1, 0);
  ledcWrite(CH_B2, 0);
}

// Stop all
void stopBoth() {
  motorAStop();
  motorBStop();
}
