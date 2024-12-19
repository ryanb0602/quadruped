#include <Arduino.h>
#include <kinecore.h>
#include <motorcore.h>

kinecore kine;
motorcore motor;

#define MOTOR_1_PWM1 15
#define MOTOR_1_PWM2 16

#define MOTOR_2_PWM1 17
#define MOTOR_2_PWM2 18

void setup() {
  Serial.begin(115200);

  motor.set_leg_pins(0, MOTOR_1_PWM1, MOTOR_1_PWM2, MOTOR_2_PWM1, MOTOR_2_PWM2);

  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

