#include <kinecore.h>

void leg::set_ideal_theta(leg_thetas thetas) {
    this->ideal_a = thetas.angle_a;
    this->ideal_b = thetas.angle_b;

    //code to update ideal xy
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