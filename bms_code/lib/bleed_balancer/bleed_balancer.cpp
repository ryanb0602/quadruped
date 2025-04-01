#include <bleed_balancer.h>

#include <io_debug_tool.h>

bleed_balancer::bleed_balancer(float* c3v6_val, float* c7v2_val, float* c10v8_val, float* c14v4_val, float* c18v0_val, float* c21v6_val, float* c25v2_val, float* c28v8_val) {
    this->c3v6_val = c3v6_val;
    this->c7v2_val = c7v2_val;
    this->c10v8_val = c10v8_val;
    this->c14v4_val = c14v4_val;
    this->c18v0_val = c18v0_val;
    this->c21v6_val = c21v6_val;
    this->c25v2_val = c25v2_val;
    this->c28v8_val = c28v8_val;

    for (int i = 0; i < 8; i++) {
        pinMode(DRAIN_ARRAY[i], OUTPUT);
        digitalWrite(DRAIN_ARRAY[i], LOW);
    }

    cell_vals = std::vector<float>(8, 0.0f);
    debug_print(MAIN_AND_SUB_FUNCTIONS, "BB: CONSTRUCTED BLEED_BALANCER AND INITIALIZED CELL VALS");
}

bool bleed_balancer::update() {
    bool return_val = false;
    this->calc_cells();
    if (!balance_enabled) {
        return return_val;
    }

    unsigned long current_time = millis();
    if (current_time - last_update >= 1000 / BALANCE_LOOP_SPEED) {
        last_update = current_time;

        if (back_balance_state) {
            debug_print(MAIN_AND_SUB_FUNCTIONS, "BB: RUNNING BACK BALANCE");
            back_balance();
            return return_val;
        }

        float v1 = cell_vals[current_cell];
        float v2 = cell_vals[current_cell-1];

        float *high_cell;
        float *low_cell;

        int drain_pin;

        if (v1 > v2 && v1 - v2 >= BALANCING_THRESHOLD) {
            drain_pin = DRAIN_ARRAY[current_cell];
            high_cell = &v1;
            low_cell = &v2;
        } else if (v1 < v2 && v2 - v1 >= BALANCING_THRESHOLD) {
            drain_pin = DRAIN_ARRAY[current_cell-1];
            high_cell = &v2;
            low_cell = &v1;
        } else {
            digitalWrite(DRAIN_ARRAY[current_cell], LOW);
            digitalWrite(DRAIN_ARRAY[current_cell-1], LOW);

            if (current_min > v1) {
                current_min = v1;
                min_cell = current_cell;
                back_balance_state = true;
                debug_print(MAIN_AND_SUB_FUNCTIONS, "BB: UPDATED CURRENT MIN AND ENTERING BACK BALANCE STATE");
            }

            current_cell++;
            if (current_cell >= 7) {
                current_cell = 1;
                return_val = true;
                debug_print(MAIN_AND_SUB_FUNCTIONS, "BB: CELLS BALANCED");
            }

            error = 0;
            error_sum = 0;

            return return_val;
        }

        error = *high_cell - *low_cell;
        error_sum += error;
        float output = BALANCE_KP * error + BALANCE_KI * error_sum;
        analogWrite(drain_pin, constrain(output, 0, 255));
        std::string debug_out = "BB: APPLIED PWM " + std::to_string(constrain(output, 0, 255)) + "TO DRAIN " + std::to_string(drain_pin);
        debug_print(MAIN_SUB_AND_NUMERICAL_DATA, debug_out);
    }
    return return_val;
}

//this function is going to definetely need scaling average voltage divider function values are set, this is pretty much a placeholder currently
void bleed_balancer::calc_cells() {
    cell_vals[0] = *c3v6_val;
    cell_vals[1] = *c7v2_val - *c3v6_val;
    cell_vals[2] = *c10v8_val - *c7v2_val;
    cell_vals[3] = *c14v4_val - *c10v8_val;
    cell_vals[4] = *c18v0_val - *c14v4_val;
    cell_vals[5] = *c21v6_val - *c18v0_val;
    cell_vals[6] = *c25v2_val - *c21v6_val;
    cell_vals[7] = *c28v8_val - *c25v2_val;
}

void bleed_balancer::back_balance() {
    if (cell_vals[min_cell] > current_min && cell_vals[min_cell] - current_min >= BALANCING_THRESHOLD) {
        error = cell_vals[min_cell] - current_min;
        error_sum += error;
        float output = BALANCE_KP * error + BALANCE_KI * error_sum;
        analogWrite(DRAIN_ARRAY[min_cell], constrain(output, 0, 255));
        debug_print(MAIN_SUB_AND_NUMERICAL_DATA, "BB: BACK BALANCING ACTIVE CELL WITH PWM");
    } else {
        digitalWrite(DRAIN_ARRAY[min_cell], LOW);
        min_cell--;
        debug_print(MAIN_AND_SUB_FUNCTIONS, "BB: BACK BALANCED CELL COMPLETE, MOVING TO PREVIOUS CELL");
        if (min_cell < 0) {
            min_cell = 7;
            back_balance_state = false;
            error = 0;
            error_sum = 0;
            debug_print(MAIN_AND_SUB_FUNCTIONS, "BB: BACK BALANCE COMPLETE, RETURNING TO NORMAL BALANCING");
        }
    }
}
