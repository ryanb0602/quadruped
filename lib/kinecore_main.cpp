#include <kinecore.h>

leg_deltas kinecore::all_leg_deltas() {

    leg_deltas return_structure;
    for (int i = 0; i < 4; i++) {

        leg_thetas real_thetas = this->leg_arr[i].real_thetas();
        leg_thetas ideal_thetas = this->leg_arr[i].adj_ideal_thetas();

        return_structure.a_vals[i] = ideal_thetas.angle_a - real_thetas.angle_a;
        return_structure.b_vals[i] = ideal_thetas.angle_b - real_thetas.angle_b;
    }

}