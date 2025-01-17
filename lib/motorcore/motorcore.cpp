#include <motorcore.h>
#include <io_debug_tool.h>
#include <string>

#include <Arduino.h>

void motorcore::bind_kine(kinecore *kine) {
    this->kine = kine;
    std::string debug_string = "MOTORCORE: KINECORE BOUND";
    debug_print(MAIN_AND_SUB_FUNCTIONS, debug_string);
}

void motorcore::set_leg_pins(int leg_num, int pin_1_a, int pin_1_b, int pin_2_a, int pin_2_b) {
    this->leg_arr[leg_num].set_leg_pins(pin_1_a, pin_1_b, pin_2_a, pin_2_b);
    std::string debug_string = "MOTORCORE: LEG PINS SET";
    debug_print(MAIN_AND_SUB_FUNCTIONS, debug_string);
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

int motorcore::get_real_ADC_val(int leg_num, int a_b) {
    return this->leg_arr[leg_num].get_real_ADC_val(a_b);
}

void motorcore::set_ADC_pin(int leg_num, int pin_a, int pin_b) {
    this->leg_arr[leg_num].set_ADC_pins(pin_a, pin_b);
}

void motorcore::print_angle(int leg_num, int a_b) {
    this->leg_arr[leg_num].print_angle(a_b);
}

void motorcore::calibrate_leg(int leg_num, float mech_max_a, float mech_min_a, float mech_max_b, float mech_min_b) {
    this->leg_arr[leg_num].calibrate_leg(mech_max_a, mech_min_a, mech_max_b, mech_min_b);
}