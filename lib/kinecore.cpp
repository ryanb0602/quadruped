#include <kinecore.h>

void leg::set_ideal_theta(leg_thetas thetas) {
    this->ideal_a = thetas.angle_a;
    this->ideal_b = thetas.angle_b;
}

leg_thetas leg::ideal_thetas() {
    leg_thetas return_structure = {
        .angle_a = this->ideal_a,
        .angle_b = this->ideal_b
    };
    return return_structure;
}

leg_thetas leg::real_thetas() {
    leg_thetas return_structure = {
        .angle_a = this->real_a,
        .angle_b = this->real_b
    };
    return return_structure;
}

leg_position leg::forward_kin(float angle_a, float angle_b) {
    //right now, this assumes theta a is always pos, theta b less than 90
    //may change based on mechanical definitions

    leg_position return_structure = {
        .pos_x = (this->seg_lens * sin(angle_a)) - (this->seg_lens * cos(angle_b)),
        .pos_y = (this->seg_lens * cos(angle_a)) - (this->seg_lens * sin(angle_b))
    };
    return return_structure;
}

leg_position leg::ideal_pos() {
    return this->forward_kin(this->ideal_a, this->ideal_b);
}

leg_position leg::real_pos() {
    return this->forward_kin(this->real_a, this->real_b);
}