#ifndef MOTORCORE_H
#define MOTORCORE_H

#include <vector>
#include <kinecore.h>
#include <QuickPID.h>
#include <ortho-hall.h>
#include <vector>

class motor {
    public:
        //set motor identifier, lets debug printouts know motor references
        void set_ident(int ident);

        //error state right now needs a full implementation, only stops new PWM values from being set
        //trigger error state
        void trigger_error();

        //set pwm pins
        void set_pwm_pins(int pin_1, int pin_2);
        
        //initialize hall sensor
        void init_hall(int pin_x, int pin_y, sensor_variables sensor);

        //set between -255 and 255
        void set_pwm_values(int value);

        //update theta and speed
        void update_theta();

        //set ideal theta
        void set_ideal_theta(float theta);

        //initialize position PID controller
        void init_pos(float p, float i, float d);
        //initialize speed PID controller
        void init_speed(float p, float i, float d);

        //update PID controllers, to be called every loop or at update frequency
        void update_PID();

        //poll adc
        static int poll_adc(int pin);

        //print angle of motor
        void print_angle();

        //calibrate motor
        void calibrate(float mech_max, float mech_min);

    private:
        int ident;

        bool error_state = false;

        angle_sensor *hall_sensor;
        int angle_offset;

        int pwm_pin1;
        int pwm_pin2;

        int pin_x;
        int pin_y;

        float target;

        QuickPID *position_PID;
        QuickPID *speed_PID;

        float target_speed;

        float speed;

        float last_pos;
        float time_of_last_pos;

        int pwm_value;

        float avg_deriv(std::vector<float> &data_set);
};

class motorcore {
    public:


    private:
        //kinecore linkage
        kinecore *kine;
        
        /*motor array mapping
        leg 0 - a = 0, b = 1
        leg 1 - a = 2, b = 3
        leg 2 - a = 4, b = 5
        leg 3 - a = 6, b = 7*/
        //motor array
        motor *motors[8];

};

#endif