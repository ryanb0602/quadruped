#include <Arduino.h>
#include <kinecore.h>
#include <motorcore.h>
#include <io_debug_tool.h>
#include <CONSTANT.h>

debug_tool debug;

kinecore kine;
motorcore motorController;

void setup() {
  Serial.begin(115200);

  debug.set_verbosity(MAIN_FUNCTIONS, debug);

  debug_print(MAIN_FUNCTIONS, "PROGRAM INIT");

  motorController.initialize_motor(0, MOTOR0);

  motorController.calibrate_motor(0);
  
}

unsigned long last_time = 0;

void loop() {
  if (millis() - last_time > 5000) {
    motorController.print_angle(0);
    last_time = millis();
  }
}

