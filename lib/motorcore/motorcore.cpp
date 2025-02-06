#include <motorcore.h>
#include <io_debug_tool.h>
#include <string>

#include <Arduino.h>

void motorcore::initialize_motor(int motor_ident, const motor_initialize_struct &motor_init) {
    this->motors[motor_ident] = new motor;
    this->motors[motor_ident]->set_ident(motor_ident);
    this->motors[motor_ident]->set_pwm_pins(motor_init.pwm_pin1, motor_init.pwm_pin2);
    this->motors[motor_ident]->init_hall(motor_init.hall_pin_x, motor_init.hall_pin_y, motor_init.sensor);
    this->motors[motor_ident]->init_pos(motor_init.p_p, motor_init.i_p, motor_init.d_p);
    this->motors[motor_ident]->init_speed(motor_init.p_s, motor_init.i_s, motor_init.d_s);
    this->motors[motor_ident]->set_mech_limits(motor_init.mech_min, motor_init.mech_max);
}

void motorcore::bind_kine(kinecore *kine) {
    this->kine = kine;
}

void motorcore::update_PID() {
    for (int i = 0; i < 8; i++) {
        this->motors[i]->update_PID();
    }
}

void motorcore::update_PID(int motor_ident) {
    this->motors[motor_ident]->update_PID();
}

void motorcore::print_angle(int motor_ident) {
    this->motors[motor_ident]->print_angle();
}

void motorcore::calibrate_motor() {
    for (int i = 0; i < 8; i++) {
        this->motors[i]->calibrate();
    }
}

void motorcore::calibrate_motor(int motor_ident) {
    this->motors[motor_ident]->calibrate();
}

void motorcore::update_kine() {
    //take theta values from kine and feed them to motors   
}