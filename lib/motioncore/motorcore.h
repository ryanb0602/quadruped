#ifndef MOTORCORE_H
#define MOTORCORE_H

#include <vector>
#include <kinecore.h>

class motor {
    public:
        void set_pwm_pins(int pin_1, int pin_2);
        void set_adc_pin(int pin);
        void set_lookup_table(int table[][2], int table_size);

        //set between -255 and 255
        void set_pwm_values(int value);

        leg_thetas get_thetas();
    private:
        std::vector<std::pair<float, float>> lookup_table;
        int poll_adc();
        int pwm_pin1;
        int pwm_pin2;
        int adc_pin;
};

class motorcore {
    public:
        motor motor_arr[8];
};

#endif