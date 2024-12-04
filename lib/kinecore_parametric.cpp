#include <kinecore.h>

void parametric::set_function(leg_thetas (*function)(int t)) {
    this->function = function;
}

void parametric::set_update_rate(int rate) {
    this->update_rate = rate;
}

int parametric::get_update_rate() {
    return this->update_rate;
}

void parametric::set_runtime(int t) {
    this->runtime = t;
}

int parametric::get_runtime() {
    return this->runtime;
}

leg_thetas parametric::get_current_vals(int t) {
    return function(t);
}