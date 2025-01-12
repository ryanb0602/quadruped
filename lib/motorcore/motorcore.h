#ifndef MOTORCORE_H
#define MOTORCORE_H

#include <vector>
#include <kinecore.h>
#include <QuickPID.h>

class motor {
    public:
        void set_ident(int ident);

        void trigger_error();

        void set_pwm_pins(int pin_1, int pin_2);
        void set_adc_pin(int pin);

        //set between -255 and 255
        void set_pwm_values(int value);

        void update_theta();

        void set_ideal_theta(float theta);

        void init_pos(float p, float i, float d);
        void init_speed(float p, float i, float d);

        void update_PID();

        int poll_adc();

        void print_angle();

    private:
        int ident;

        bool error_state = false;

        std::vector<std::pair<float, float>> lookup_table;

        int pwm_pin1;
        int pwm_pin2;

        int adc_pin;

        float target;

        QuickPID *position_PID;
        QuickPID *speed_PID;

        float target_speed;

        float speed;

        float last_pos;
        float time_of_last_pos;

        int pwm_value;
};

class motor_leg {
    public:
        void init_pos_PID(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b);
        void init_speed_PID(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b);
        void set_ideal_thetas(float a, float b);
        void set_leg_pins(int pin_1_a, int pin_1_b, int pin_2_a, int pin_2_b);
        void update_PID();
        int get_real_ADC_val(int a_b);
        void set_ADC_pins(int pin_a, int pin_b);
        void print_angle(int a_b);
    private:
        motor *motor_a;
        motor *motor_b;
};

class motorcore {
    public:
        void set_leg_pins(int leg_num, int pin_1_a, int pin_1_b, int pin_2_a, int pin_2_b);
        void set_ADC_pin(int leg_num, int pin_a, int pin_b);
        void init_leg_pPIDS(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b);
        void init_leg_sPIDS(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b);
        
        void bind_kine(kinecore *kine);
        void update_ideal_thetas();

        void update_PID();
        void update_PID(int leg_num);

        //0 for a, 1 for b
        int get_real_ADC_val(int leg_num, int a_b);

        void print_angle(int leg_num, int a_b);

    private:
        kinecore *kine;
        motor_leg leg_arr[4];
};

#endif