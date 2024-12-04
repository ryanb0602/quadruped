#include <kinecore.h>
#include <paracore.h>

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

}