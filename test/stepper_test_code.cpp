#include <Arduino.h>

#define STEP_PIN 17
#define DIR_PIN 18

void stepMotor(int steps);

void setup() {
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    // Move forward
    Serial.println("Moving forward");
    digitalWrite(DIR_PIN, HIGH);
    stepMotor(200);
    delay(1000);

    // Move backward
    Serial.println("Moving backward");
    digitalWrite(DIR_PIN, LOW);
    stepMotor(200);
    delay(1000);
}

void stepMotor(int steps) {
    for (int i = 0; i < steps; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(1200);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(1200);
    }
}
