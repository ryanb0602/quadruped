#include <motorcore.h>

#include <Arduino.h>

void motor::set_ident(int ident) {
    this->ident = ident;
}

void motor::trigger_error() {
    Serial.print("Error triggered on motor: ");
    Serial.print(this->ident);
    Serial.println(", PWM set to 0");
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

void motor::set_lookup_table(int table[][2], int table_size) {
    this->lookup_table.clear(); // Clear any existing data

    for (int i = 0; i < table_size; ++i) {
        this->lookup_table.emplace_back(table[i][0], table[i][1]); // Convert and store
    }
}

void motor::set_pwm_values(int value) {
    if (this->error_state) {
        return;
    }
    if (value == 0) {
        digitalWrite(this->pwm_pin1, LOW);
        digitalWrite(this->pwm_pin2, LOW);
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
    for (int i = 0; i < this->lookup_table.size() - 1; i++) {
        if (adc_value >= this->lookup_table[i].first) {
            float this_pos =  (this->lookup_table[i].second + (adc_value * (this->lookup_table[i + 1].second - this->lookup_table[i].second) / (this->lookup_table[i + 1].first - this->lookup_table[i].first)));
            this->speed = (this_pos - this->last_pos) / (millis() - this->time_of_last_pos);
            this->last_pos = this_pos;
            this->time_of_last_pos = millis();
        }
    }
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