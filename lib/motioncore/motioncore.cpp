#include <motorcore.h>
#include <Arduino.h>

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