#include <para_funcs.h>

#include <kinecore.h>
#include <math.h>

leg_position test_para(int t) {
    float x = sinf(M_PI * t / 1000);
    float y = -(cosf(M_PI * t / 1000) - 8);

    leg_position return_pos = {
        .pos_x = x,
        .pos_y = y
    };

    return return_pos;
}