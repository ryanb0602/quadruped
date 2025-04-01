#include <bms_safety.h>

#include <esp_task_wdt.h>

#include "driver/temp_sensor.h"


extern "C" {
    #include "esp_system.h"
}

bms_safety::bms_safety(float* therm1, float* therm2, float* load_current, float* charge_current) {
    this->therm1 = therm1;
    this->therm2 = therm2;
    this->load_current = load_current;
    this->charge_current = charge_current;

    esp_register_shutdown_handler(&__FATAL_SHUTDOWN);

    boot_check();

    esp_task_wdt_init(3, true);
    esp_task_wdt_add(NULL); 

    temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
    temp_sensor.dac_offset = TSENS_DAC_L2;  // TSENS_DAC_L2 is default; L4(-40°C ~ 20°C), L2(-10°C ~ 80°C), L1(20°C ~ 100°C), L0(50°C ~ 125°C)
    temp_sensor_set_config(temp_sensor);
    temp_sensor_start();
}

//this doesnt yet convert therm vals to celsius, need to do that
void bms_safety::update() {
    esp_task_wdt_reset();

    float mcu_temp = 0;
    temp_sensor_read_celsius(&mcu_temp);

    if (mcu_temp > MCU_TEMP_MAX) {
        safe_shutdown(1);
    }

    if (*therm1 > THERM1_MAX || *therm1 < THERM1_MIN) {
        safe_shutdown(2);
    }

    if (*therm2 > THERM2_MAX || *therm2 < THERM2_MIN) {
        safe_shutdown(3);
    }

    if (*load_current > LOAD_CURRENT_MAX) {
        safe_shutdown(5);
    }

    if (*charge_current > CHARGE_CURRENT_MAX) {
        safe_shutdown(6);
    }

}

//logic to determine if last shutdown was problematic, find some mechanism to verify if boot should still continue
void bms_safety::boot_check() {

}