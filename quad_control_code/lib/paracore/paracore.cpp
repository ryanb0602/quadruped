#include <kinecore.h>
#include <paracore.h>

void parametric::set_function(leg_position (*function)(int t)) {
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

leg_position parametric::get_current_vals(int t) {
    return function(t);
}

int parametric::get_starttime() {
    return this->start_time;
}

int parametric::get_lastupdate() {
    return this->last_update;
}

void parametric::set_lastupdate(int t) {
    this->last_update = t;
}