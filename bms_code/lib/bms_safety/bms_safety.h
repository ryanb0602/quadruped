#include <Arduino.h>
#include <pindefs.h>
#include <thresholds.h>
#include <error_codes.h>

#ifndef BMS_SAFETY_H
#define BMS_SAFETY_H

class bms_safety {
    public:

        bms_safety(float* therm1, float* therm2, float* load_current, float* charge_current);

        void update();

    private:
        void boot_check();

        void safe_shutdown(int code);

        float* therm1;
        float* therm2;
        float* load_current;
        float* charge_current;

};

void IRAM_ATTR __FATAL_SHUTDOWN();

#endif