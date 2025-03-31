#include <kinecore.h>
#include <string>
#include <io_debug_tool.h>

kinecore::kinecore() {
    std::string debug_string = "KINECORE CLASS INIT";
    debug_print(MAIN_AND_SUB_FUNCTIONS, debug_string);
    for (int i  = 0; i < 4; i ++) {
        this->leg_arr[i].set_ident(i);
        debug_string = "KINECORE, LEG " + std::to_string(i) + " INIT";
        debug_print(MAIN_SUB_AND_NUMERICAL_DATA, debug_string);
    }
}

void kinecore::set_segment_lens(float len) {
    leg *leg_arr = this->leg_arr;
    for (int i = 0; i < 4; i ++) {
        leg_arr[i].set_seg_len(len); 
    }
}

void kinecore::bind_parametric(int leg_n, parametric *function) {
    this->parametric_handler.add_active(function, &this->leg_arr[leg_n]);
    std::string debug_string = "KINECORE, BOUND LEG " + std::to_string(leg_n) + " TO PARAMETRIC FUNCTION";
    debug_print(MAIN_SUB_AND_NUMERICAL_DATA, debug_string);
}

void kinecore::update_paras() {
    this->parametric_handler.update_all();
}

leg_position kinecore::leg_x_y(int leg_n) {
    return this->leg_arr[leg_n].ideal_pos();
}

leg_thetas kinecore::leg_thetas_vals(int leg_n) {
    return this->leg_arr[leg_n].ideal_thetas();
}