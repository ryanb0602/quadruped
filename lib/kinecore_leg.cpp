#include <kinecore.h>

#include <math.h>

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
        .pos_y = (this->seg_lens * cos(angle_a)) + (this->seg_lens * sin(angle_b))
    };
    return return_structure;
}

leg_position leg::ideal_pos() {
    return this->forward_kin(this->ideal_a, this->ideal_b);
}

leg_position leg::real_pos() {
    return this->forward_kin(this->real_a, this->real_b);
}

bool leg::set_ideal_x_y(leg_position position) {

    float ee_x = position.pos_x;
    float ee_y = position.pos_y;

    float r = sqrt(powf(ee_x, 2) + powf(ee_y, 2));
    float phi = atan2f(ee_y, ee_x);

    if (r > 2 * this->seg_lens) {
        return false;
    }

    float ideal_a = phi - acosf(powf(r, 2) / (2 * this->seg_lens * r));
    float ideal_b = asinf((ee_y - (this->seg_lens * cos(ideal_a))) / this->seg_lens);

    leg_thetas ideals = {
        .angle_a = ideal_a,
        .angle_b = ideal_b
    };

    this->set_ideal_theta(ideals);

    return true;
}