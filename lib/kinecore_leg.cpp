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

bool leg::set_ideal_x_y(leg_position position) {

    float ee_x = position.pos_x;
    float ee_y = position.pos_y;

    // Length of the segments (assumed equal in this case)
    float L = this->seg_lens;

    // Distance to the end-effector
    float distance = sqrtf(powf(ee_x, 2) + powf(ee_y, 2));

    // Check if the target is reachable
    if (distance > 2 * L || distance < 0) {
        return false;
    }

    // Calculate theta_a (joint 1 angle)
    float ideal_a = atan2f(ee_y, ee_x) - acosf((powf(L, 2) + powf(distance, 2) - powf(L, 2)) / (2 * L * distance));

    // Calculate theta_b (joint 2 angle relative to joint 1)
    float ideal_b = acosf((powf(distance, 2) - 2 * powf(L, 2)) / (-2 * powf(L, 2)));

    // Convert to absolute angle from horizontal
    float absolute_b = ideal_a - ideal_b - (M_PI / 2);

    leg_thetas ideals = {
        .angle_a = ideal_a,
        .angle_b = absolute_b
    };

    this->set_ideal_theta(ideals);

    return true;
}

leg_thetas leg::adj_ideal_thetas() {
    leg_thetas return_structure = {
        .angle_a = this->ideal_a + this->stable_offset_a + this->hip_offset_a,
        .angle_b = this->ideal_b + this->stable_offset_b + this->hip_offset_b
    };
    return return_structure;
}

void leg::set_seg_len(float len) {
    this->seg_lens = len;
}