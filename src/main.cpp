#include <Arduino.h>
#include <kinecore.h>
#include <motorcore.h>
#include <io_debug_tool.h>
#include <CONSTANT.h>

debug_tool debug;

kinecore kine;
motorcore motorController;

#define MOTOR_1_PWM1 17
#define MOTOR_1_PWM2 18

#define MOTOR_2_PWM1 15
#define MOTOR_2_PWM2 16

#define MOTOR_1_ADC1 5
#define MOTOR_2_ADC2 4

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

  debug.set_verbosity(MAIN_FUNCTIONS, debug);

  debug_print(MAIN_FUNCTIONS, "PROGRAM INIT");

  //for lookup test
  motorController.initialize_motor(0, MOTOR0);
  /*
  motorController.bind_kine(&kine);

  motorController.set_leg_pins(0, MOTOR_1_PWM1, MOTOR_1_PWM2, MOTOR_2_PWM1, MOTOR_2_PWM2);
  motorController.init_leg_pPIDS(LEG_A_PKP, LEG_A_PKI, LEG_A_PKD, LEG_B_PKP, LEG_B_PKI, LEG_B_PKD);
  motorController.init_leg_sPIDS(LEG_A_SKP, LEG_A_SKI, LEG_A_SKD, LEG_B_SKP, LEG_B_SKI, LEG_B_SKD);

  int lookup_table_a[LEG_LOOKUP_A_LEN][2] = LEG_LOOKUP_A;
  int lookup_table_b[LEG_LOOKUP_B_LEN][2] = LEG_LOOKUP_B;

  motorController.set_leg_lookup_table(0, lookup_table_a, lookup_table_b, LEG_LOOKUP_A_LEN); 

  */ 

  motorController.calibrate_motor(0);
  
}

unsigned long last_time = 0;

void loop() {
  //Reading out adcs
  //motorController.update_PID(0);
  if (millis() - last_time > 5000) {
    motorController.print_angle(0);
    last_time = millis();
  }
  

  /*
  motorController.update_ideal_thetas();
  motorController.update_PID();
  */
}

