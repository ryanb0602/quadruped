#include <kinecore.h>
#include <paracore.h>
#include <para_funcs.h>


extern "C" {

kinecore kinematic;

int test_function() {
    return 200;
}

void setup(float seg_lens) {
    kinematic.set_segment_lens(seg_lens);
}

void set_real_thetas(int leg, float a, float b) {
    kinematic.set_real_thetas(leg, a, b);
}

leg_deltas get_deltas() {
    return kinematic.all_leg_deltas();
}

void setup_basic_test() {
    parametric *test_parametric = new parametric;

    test_parametric->set_function(test_para);
    test_parametric->set_runtime(10000);

    kinematic.bind_parametric(0, test_parametric);
}

void update_basic_test() {
    kinematic.update_paras();
}

leg_position data_basic_test() {
    return kinematic.leg_x_y(0);
}

leg_thetas leg_theta_vals(int leg_n) {
    return kinematic.leg_thetas_vals(leg_n);
}

}