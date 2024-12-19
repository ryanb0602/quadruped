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
        void set_lookup_table(int table[][2], int table_size);

        //set between -255 and 255
        void set_pwm_values(int value);

        void update_theta();

        void set_ideal_theta(float theta);

        void init_pos(float p, float i, float d);
        void init_speed(float p, float i, float d);

        void update_PID();

    private:
        int ident;

        bool error_state = false;

        std::vector<std::pair<float, float>> lookup_table;

        int poll_adc();

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
        void set_lookup_table(int table_a[][2], int table_b[][2], int table_size);
    private:
        motor *motor_a;
        motor *motor_b;
};

class motorcore {
    public:
        void set_leg_pins(int leg_num, int pin_1_a, int pin_1_b, int pin_2_a, int pin_2_b);
        void init_leg_pPIDS(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b);
        void init_leg_sPIDS(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b);
        void set_leg_lookup_table(int leg_num, int table_a[][2], int table_b[][2], int table_size);

        void bind_kine(kinecore *kine);
        void update_ideal_thetas();

        void update_PID();
        void update_PID(int leg_num);

    private:
        kinecore *kine;
        motor_leg leg_arr[4];
};

#endif