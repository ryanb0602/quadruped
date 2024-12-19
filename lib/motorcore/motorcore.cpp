#include <motorcore.h>

#include <Arduino.h>

void motorcore::bind_kine(kinecore *kine) {
    this->kine = kine;
}

void motorcore::set_leg_pins(int leg_num, int pin_1_a, int pin_1_b, int pin_2_a, int pin_2_b) {
    this->leg_arr[leg_num].set_leg_pins(pin_1_a, pin_1_b, pin_2_a, pin_2_b);
}

void motorcore::init_leg_pPIDS(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b) {
    for (int i = 0; i < 4; ++i) {
        this->leg_arr[i].init_pos_PID(p_a, i_a, d_a, p_b, i_b, d_b);
    }
}

void motorcore::init_leg_sPIDS(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b) {
    for (int i = 0; i < 4; ++i) {
        this->leg_arr[i].init_speed_PID(p_a, i_a, d_a, p_b, i_b, d_b);
    }
}

void motorcore::set_leg_lookup_table(int leg_num, int table_a[][2], int table_b[][2], int table_size) {
    this->leg_arr[leg_num].set_lookup_table(table_a, table_b, table_size);
}

void motorcore::update_ideal_thetas() {
    for (int i = 0; i < 4; ++i) {
        leg_thetas thetas = this->kine->leg_thetas_vals(i);
        this->leg_arr[i].set_ideal_thetas(thetas.angle_a, thetas.angle_b);
    }
}

void motorcore::update_PID() {
    for (int i = 0; i < 4; ++i) {
        this->leg_arr[i].update_PID();
    }
}

void motorcore::update_PID(int leg_num) {
    this->leg_arr[leg_num].update_PID();
}