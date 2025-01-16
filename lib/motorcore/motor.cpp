#include <motorcore.h>

#include <Arduino.h>
#include <string>
#include <io_debug_tool.h>
#include <math.h>

void motor::set_ident(int ident) {
    this->ident = ident;
}

void motor::trigger_error() {
    
    std::string debug_string = "MOTOR " + std::to_string(this->ident) + " ERROR TRIGGERED";
    debug_print(SILENT, debug_string);

    this->set_pwm_values(0);
    this->error_state = true;
}

void motor::set_pwm_pins(int pin_1, int pin_2) {
    pinMode(pin_1, OUTPUT);
    pinMode(pin_2, OUTPUT);
    this->pwm_pin1 = pin_1;
    this->pwm_pin2 = pin_2;
}

void motor::init_hall(int pin_x, int pin_y, sensor_variables sensor) {
    this->pin_x = pin_x;
    this->pin_y = pin_y;
    this->hall_sensor = new angle_sensor(pin_x, pin_y, sensor, *this->poll_adc);
}

void motor::set_pwm_values(int value) {
    if (this->error_state) {
        return;
    }
    if (value == 0) {
        analogWrite(this->pwm_pin1, 0);
        analogWrite(this->pwm_pin2, 0);
    } else if (value < 0) {
        analogWrite(this->pwm_pin1, 0);
        analogWrite(this->pwm_pin2, abs(value));
    } else {
        analogWrite(this->pwm_pin1, value);
        analogWrite(this->pwm_pin2, 0);
    }
}

void motor::update_theta() {
    float current_angle = this->hall_sensor->read_angle() + this->angle_offset;
    this->speed = (current_angle - this->last_pos) / (millis() - this->time_of_last_pos);
    this->time_of_last_pos = millis();
    this->last_pos = current_angle;
}

void motor::set_ideal_theta(float theta) {
    this->target = theta;
}

void motor::init_pos(float p, float i, float d) {
    this->position_PID = new QuickPID(&this->last_pos, &this->target_speed, &this->target, p, i, d, QuickPID::Action::direct);
    this->position_PID->SetMode(QuickPID::Control::automatic);
    this->position_PID->SetOutputLimits(-100, 100);
}

void motor::init_speed(float p, float i, float d) {
    this->position_PID = new QuickPID(&this->speed, (float*)&this->pwm_value, &this->target_speed, p, i, d, QuickPID::Action::direct);
    this->speed_PID->SetMode(QuickPID::Control::automatic);
    this->speed_PID->SetOutputLimits(-255, 255);
}

void motor::update_PID() {
    this->update_theta();

    this->position_PID->Compute();
    this->speed_PID->Compute();

    this->set_pwm_values(this->pwm_value);
}

int motor::poll_adc(int pin) {
    return analogRead(pin);
}

void motor::print_angle() {
    this->update_theta();
    std::string debug_string = "Motor: " + std::to_string(this->ident) + " Angle: Rad: " + std::to_string(this->hall_sensor->read_angle() - this->angle_offset) + " Degrees: " + std::to_string(this->hall_sensor->read_angle_degrees() - (this->angle_offset*180/M_PI));
    debug_print(SILENT, debug_string);
}

void motor::calibrate(float mech_max, float mech_min) {
    std::string debug_string = "Calibrating motor " + std::to_string(this->ident);
    debug_print(MAIN_FUNCTIONS, debug_string);

    this->set_pwm_values(100);

    debug_print(MAIN_AND_SUB_FUNCTIONS, "MOVING TOWARDS MAXIMUM");

    delay(500);

    std::vector<float> readings;

    unsigned long last_time = millis();
    unsigned long last_reading = millis();

    float read_max;
    float read_min;

    while (1) {
        if (last_reading - millis() >= 10) {

            readings.push_back(this->hall_sensor->read_angle());

            last_reading = millis();
        }
        if (last_time - millis() >= 1000) {

            float avg = this->avg_deriv(readings);

            debug_print(MAIN_SUB_AND_NUMERICAL_DATA, "Average Derivative: ");
            debug_string = avg;
            debug_print(MAIN_SUB_AND_NUMERICAL_DATA, debug_string);

            if (abs(avg) <= 1) {
                this->set_pwm_values(0);
                read_max = this->hall_sensor->read_angle();

                debug_string = "MAXIMUM REACHED: " + std::to_string(read_max);

                debug_print(MAIN_SUB_AND_NUMERICAL_DATA, debug_string);

                readings.clear();
                break;
            }
        }
    }

    debug_print(MAIN_AND_SUB_FUNCTIONS, "MOVING TOWARDS MINIMUM");

    this->set_pwm_values(-100);
    delay(500);

    while (1) {
        if (last_reading - millis() >= 10) {

            readings.push_back(this->hall_sensor->read_angle());

            last_reading = millis();
        }
        if (last_time - millis() >= 1000) {

            float avg = this->avg_deriv(readings);

            debug_print(MAIN_SUB_AND_NUMERICAL_DATA, "Average Derivative: ");
            debug_string = avg;
            debug_print(MAIN_SUB_AND_NUMERICAL_DATA, debug_string);

            if (abs(avg) <= 1) {
                this->set_pwm_values(0);
                read_min = this->hall_sensor->read_angle();

                debug_string = "MAXIMUM REACHED: " + std::to_string(read_max);

                debug_print(MAIN_SUB_AND_NUMERICAL_DATA, debug_string);

                readings.clear();
                break;
            }
        }
    }

    this->angle_offset = mech_max - read_max;

    debug_string = "Calibration done, different between read range and theoretical range: " + std::to_string(mech_max - mech_min - read_max - read_min);

}

float motor::avg_deriv(std::vector<float> &dataset) {

    float deriv_sum = 0;

    for (int i = 1; i < dataset.size(); i++) {
        deriv_sum += dataset[i] - dataset[i-1];
    }

    return deriv_sum / (dataset.size() - 1);

}