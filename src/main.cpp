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

  motor.motor_arr[0].set_pwm_pins(MOTOR_1_PWM1, MOTOR_1_PWM2);
  motor.motor_arr[1].set_pwm_pins(MOTOR_2_PWM1, MOTOR_2_PWM2);
  motor.motor_arr[0].set_pwm_values(0);
  
}

void loop() {
  motor.motor_arr[0].set_pwm_values(-100);
  motor.motor_arr[1].set_pwm_values(-100);
  delay(200);
  motor.motor_arr[0].set_pwm_values(100);
  motor.motor_arr[1].set_pwm_values(100);
  delay(200);
  Serial.println("run");
}

