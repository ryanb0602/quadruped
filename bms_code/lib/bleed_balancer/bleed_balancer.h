#include <Arduino.h>
#include <pindefs.h>
#include <vector>


#ifndef BLEED_BALANCER_H
#define BLEED_BALANCER_H

#define BALANCING_THRESHOLD 0.1f // 100mV

//yet to be tested and tuned
#define BALANCE_KP 0.1f
#define BALANCE_KI 0.01f

#define BALANCE_LOOP_SPEED 100 //hz

class bleed_balancer {
    public:
        bleed_balancer(float* c3v6_val,
            float* c7v2_val,
            float* c10v8_val,
            float* c14v4_val,
            float* c18v0_val,
            float* c21v6_val,
            float* c25v2_val,
            float* c28v8_val);

        //run every loop
        //returns true if balanced
        bool update();

        void enable_balancing() {
            balance_enabled = true;
        }

        void disable_balancing() {
            balance_enabled = false;
            min_cell = 0;
            current_min = 5;
            back_balance_state = false;
            current_cell = 1;
        }

        std::vector<float> get_cell_vals() {
            return cell_vals;
        }

    private:
        void calc_cells();
        void back_balance();
        
        bool back_balance_state;

        float *c3v6_val;
        float *c7v2_val;
        float *c10v8_val;
        float *c14v4_val;
        float *c18v0_val;
        float *c21v6_val;
        float *c25v2_val;
        float *c28v8_val;

        std::vector<float> cell_vals;

        bool balance_enabled;

        float current_min = 5;
        int min_cell;

        int current_cell;
        unsigned long last_update;

        float error;
        float error_sum;
};

#endif