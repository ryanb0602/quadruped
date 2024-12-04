#include <kinecore.h>
#include <paracore.h>

kinecore kinematic;

void setup(float seg_lens) {
    kinematic.set_segment_lens(seg_lens);
}

void set_real_thetas(int leg, float a, float b) {
    kinematic.set_real_thetas(leg, a, b);
}

leg_deltas get_deltas() {
    return kinematic.all_leg_deltas();
}