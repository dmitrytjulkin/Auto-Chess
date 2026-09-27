#include <GyverStepper.h>
#include <string.h>

#define X_STEP_PIN 54
#define X_DIR_PIN  55
#define X_EN_PIN   38

#define Y_STEP_PIN 60
#define Y_DIR_PIN  61
#define Y_EN_PIN   56

#define STEPS_PER_REV 3200  

GStepper<STEPPER2WIRE> stepperX(STEPS_PER_REV, X_STEP_PIN, X_DIR_PIN);
GStepper<STEPPER2WIRE> stepperY(STEPS_PER_REV, Y_STEP_PIN, Y_DIR_PIN);

void runUntilDone(GStepper<STEPPER2WIRE> &s);

#define RULE_STEPPER(given_cmd, direction, stepper_name,                      \
                    stepper_aim, start_response, final_response)              \
    (strcmp(cmd, given_cmd) == 0) {                                           \
      if (direction == 1) stepper_aim += STEPS_PER_REV;                       \
      else                stepper_aim -= STEPS_PER_REV;                       \
                                                                              \
      Serial.println(start_response);                                         \
                                                                              \
      stepper_name.setTarget(stepper_aim);                                    \
      runUntilDone(stepper_name);                                             \
                                                                              \
      Serial.println(final_response);                                         \
    }

#define RULE_BOTH(given_cmd, direction, start_response, final_response)       \
    (strcmp(cmd, given_cmd) == 0) {                                           \
      if (direction == 1) {x_aim += STEPS_PER_REV; y_aim += STEPS_PER_REV;}   \
      else                {x_aim -= STEPS_PER_REV; y_aim -= STEPS_PER_REV;}   \
                                                                              \
      Serial.println(start_response);                                         \
                                                                              \
      stepperX.setTarget(x_aim);                                              \
      stepperY.setTarget(y_aim);                                              \
                                                                              \
      while (stepperX.tick() | stepperY.tick()) {}                            \
                                                                              \
      Serial.println(final_response);                                         \
    }

void setup() {
  pinMode(X_EN_PIN, OUTPUT);
  digitalWrite(X_EN_PIN, LOW);
  pinMode(Y_EN_PIN, OUTPUT);
  digitalWrite(Y_EN_PIN, LOW);

  Serial.begin(9600);

  stepperX.setMaxSpeed(900);
  stepperX.setAcceleration(500);
  stepperY.setMaxSpeed(900);
  stepperY.setAcceleration(500);

  Serial.println("Ready. CMDS: x_front — X goes clockwise, y_front — Y goes clockwise, \n"
                 "x_back, y_back - cmds for X and Y going anticlockwise\n"
                 "both_front — X and Y goes clockwise, both_back - X and Y goes anticlockwise\n\n");
}

long x_aim = 0;
long y_aim = 0;

void loop() {
  if (Serial.available()) {
    char cmd[32];
    size_t len = Serial.readBytesUntil('\n', cmd, sizeof(cmd) - 1);
    cmd[len] = '\0';

    if RULE_STEPPER("x_front", 1, stepperX, x_aim, "X: goes clockwise", "X: done\n")
    
    else if RULE_STEPPER("y_front", 1, stepperY, y_aim, "Y: goes clockwise", "Y: done\n")

    else if RULE_STEPPER("x_back", -1, stepperX, x_aim, "X: goes anticlockwise", "X: done\n")

    else if RULE_STEPPER("y_back", -1, stepperY, y_aim, "Y: goes anticlockwise", "Y: done\n")

    else if RULE_BOTH("both_front", 1, "X, Y: go clockwise", "X, Y: done")

    else if RULE_BOTH("both_back", -1, "X, Y: go anticlockwise", "X, Y: done")
  }
}

// Крутит мотор, пока он не доедет до цели
void runUntilDone(GStepper<STEPPER2WIRE> &s) {
  while (s.tick()) {}
}