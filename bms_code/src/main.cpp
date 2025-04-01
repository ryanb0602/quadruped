#include <Arduino.h>
#include <pindefs.h>
#include <muxed_ina.h>
#include <bleed_balancer.h>
#include <vector>
#include <io_debug_tool.h>

float c3v6_val;
float c7v2_val;
float c10v8_val;
float c14v4_val;
float c18v0_val;
float c21v6_val;
float c25v2_val;
float c28v8_val;
float therm1_val;
float therm2_val;
float therm3_val;
float therm4_val;

debug_tool debug;

std::vector<float*> outputs = {&c3v6_val, &c7v2_val, &c10v8_val, &c14v4_val, &c18v0_val, &c21v6_val, &c25v2_val, &c28v8_val, &therm1_val, &therm2_val, &therm3_val, &therm4_val};
muxed_ina multi_voltage_reader(BMS_SDA, BMS_SCL, 0x10, 12, outputs);
//bleed_balancer balancer(&c3v6_val, &c7v2_val, &c10v8_val, &c14v4_val, &c18v0_val, &c21v6_val, &c25v2_val, &c28v8_val);

void setup() {
  debug.set_verbosity(MAIN_AND_SUB_FUNCTIONS, debug);

  multi_voltage_reader.begin(500);
}

void loop() {
  multi_voltage_reader.update();
  //balancer.update();
}

