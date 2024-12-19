#include <motorcore.h>

void motor_leg::set_leg_pins(int pin_1_a, int pin_1_b, int pin_2_a, int pin_2_b) {
    motor_a = new motor();
    motor_b = new motor();

    motor_a->set_pwm_pins(pin_1_a, pin_1_b);
    motor_b->set_pwm_pins(pin_2_a, pin_2_b);
}

void motor_leg::init_PID(float p_a, float i_a, float d_a, float p_b, float i_b, float d_b) {
    motor_a->init_pos(p_a, i_a, d_a);
    motor_b->init_pos(p_b, i_b, d_b);
}

void motor_leg::set_ideal_thetas(float a, float b) {
    motor_a->set_ideal_theta(a);
    motor_b->set_ideal_theta(b);
}

void motor_leg::update_PID() {
    motor_a->update_PID();
    motor_b->update_PID();
} 