#include <motorcore.h>

#include <Arduino.h>
#include <string>
#include <io_debug_tool.h>

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

void motor::set_adc_pin(int pin) {
    this->adc_pin = pin;
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
    int adc_value = poll_adc();
    float this_pos =  (this->lookup_table[0].second + (adc_value * (this->lookup_table[1].second - this->lookup_table[0].second) / (this->lookup_table[1].first - this->lookup_table[0].first)));
    this->speed = (this_pos - this->last_pos) / (millis() - this->time_of_last_pos);
    this->last_pos = this_pos;
    this->time_of_last_pos = millis();
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

int motor::poll_adc() {
    return analogRead(this->adc_pin);
}

void motor::print_angle() {
    this->update_theta();
    Serial.print("Motor: ");
    Serial.print(this->ident);
    Serial.print(" Angle: ");
    Serial.println(this->last_pos);
}

void motor::calibrate(float mech_max, float mech_min) {
    this->set_pwm_values(-100);

    delay(1000);

    int adc_val;
    int last_adc_val;
    unsigned long last_time = millis();

    while (1) {
        if (last_time - millis() >= 1000) {
            last_adc_val = adc_val;
            adc_val = poll_adc();

            if (abs(adc_val - last_adc_val) <= 1) {
                this->set_pwm_values(0);
                break;
            }
        }
    }
    this->lookup_table.push_back(std::make_pair(adc_val, mech_min));
    
    this->set_pwm_values(100);
    delay(1000);

    while (1) {
        if (last_time - millis() >= 1000) {
            last_adc_val = adc_val;
            adc_val = poll_adc();
            if (abs(adc_val - last_adc_val) <= 1) {
                this->set_pwm_values(0);
                break;
            }
        }
    }
    this->lookup_table.push_back(std::make_pair(adc_val, mech_max));
    Serial.println("calibr done");
    Serial.println(this->lookup_table[0].first);
    Serial.println(this->lookup_table[1].first);
}