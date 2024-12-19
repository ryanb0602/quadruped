#include <Arduino.h>
#include <kinecore.h>
#include <motorcore.h>

kinecore kine;
motorcore motorcore;

#define MOTOR_1_PWM1 15
#define MOTOR_1_PWM2 16

#define MOTOR_2_PWM1 17
#define MOTOR_2_PWM2 18

#define LEG_A_PKP .5
#define LEG_A_PKI 0
#define LEG_A_PKD 0

#define LEG_B_PKP .5
#define LEG_B_PKI 0
#define LEG_B_PKD 0

#define LEG_A_SKP .5 
#define LEG_A_SKI 0
#define LEG_A_SKD 0

#define LEG_B_SKP .5
#define LEG_B_SKI 0
#define LEG_B_SKD 0

void setup() {
  Serial.begin(115200);

  motorcore.bind_kine(&kine);

  motorcore.set_leg_pins(0, MOTOR_1_PWM1, MOTOR_1_PWM2, MOTOR_2_PWM1, MOTOR_2_PWM2);
  motorcore.init_leg_pPIDS(LEG_A_PKP, LEG_A_PKI, LEG_A_PKD, LEG_B_PKP, LEG_B_PKI, LEG_B_PKD);
  motorcore.init_leg_sPIDS(LEG_A_SKP, LEG_A_SKI, LEG_A_SKD, LEG_B_SKP, LEG_B_SKI, LEG_B_SKD);
  
  
}

void loop() {
  motorcore.update_ideal_thetas();
  motorcore.update_PID();
}

