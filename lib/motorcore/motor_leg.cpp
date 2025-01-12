#include <motorcore.h>

#include <Arduino.h>

void motor_leg::set_leg_pins(int pin_1_a, int pin_1_b, int pin_2_a, int pin_2_b) {
    motor_a = new motor();
    motor_b = new motor();

    motor_a->set_pwm_pins(pin_1_a, pin_1_b);
    motor_b->set_pwm_pins(pin_2_a, pin_2_b);
}

void motor_leg::init_pos_PID(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b) {
    motor_a->init_pos(p_a, i_a, d_a);
    motor_b->init_pos(p_b, i_b, d_b);
}

void motor_leg::init_speed_PID(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b) {
    motor_a->init_speed(p_a, i_a, d_a);
    motor_b->init_speed(p_b, i_b, d_b);
}

void motor_leg::set_ideal_thetas(float a, float b) {
    motor_a->set_ideal_theta(a);
    motor_b->set_ideal_theta(b);
}

void motor_leg::update_PID() {
    motor_a->update_PID();
    motor_b->update_PID();
}

void motor_leg::set_lookup_table(int table_a[][2], int table_b[][2], int table_size) {
    motor_a->set_lookup_table(table_a, table_size);
    motor_b->set_lookup_table(table_b, table_size);
}

void motor_leg::set_ADC_pins(int pin_a, int pin_b) {
    motor_a->set_adc_pin(pin_a);
    motor_b->set_adc_pin(pin_b);
}

int motor_leg::get_real_ADC_val(int a_b) {
    if (a_b == 0) {
        return motor_a->poll_adc();
    } else {
        return motor_b->poll_adc();
    }
}