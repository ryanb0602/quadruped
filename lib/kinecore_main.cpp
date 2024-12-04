#include <kinecore.h>

leg_deltas kinecore::all_leg_deltas() {

    leg_deltas return_structure;
    for (int i = 0; i < 4; i++) {

        leg_thetas real_thetas = this->leg_arr[i].real_thetas();
        leg_thetas ideal_thetas = this->leg_arr[i].adj_ideal_thetas();

        return_structure.a_vals[i] = ideal_thetas.angle_a - real_thetas.angle_a;
        return_structure.b_vals[i] = ideal_thetas.angle_b - real_thetas.angle_b;
    }

    return return_structure;

}

void kinecore::set_segment_lens(float len) {
    leg *leg_arr = this->leg_arr;
    for (int i = 0; i < 4; i ++) {
        leg_arr[i].set_seg_len(len); 
    }
}

void kinecore::bind_parametric(leg *targ, parametric (*function)()) {
    this->parametric_handler.add_active(function(), targ);
}

void kinecore::set_real_thetas(int leg_n, float a, float b) {
    leg *target = &this->leg_arr[leg_n];

    leg_thetas vals = {
        .angle_a = a,
        .angle_b = b
    };

    target->set_real_theta(vals);
}