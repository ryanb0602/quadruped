#include <para_funcs.h>

#include <kinecore.h>
#include <math.h>

/*
leg_position test_para(int t) {
    float x = sinf(M_PI * t / 1000);
    float y = -(cosf(M_PI * t / 1000) - 8);

    leg_position return_pos = {
        .pos_x = x,
        .pos_y = y
    };

    return return_pos;
}
*/

leg_position test_para(int t) { 
    float secs = t;

    float x = (1.0/5.0) * 16 * sinf(secs) * sinf(secs) * sinf(secs);
    float y = -(1.0/5.0) * (13 * cosf(secs) - 5 * cosf(2 * secs) - 2 * cosf(3 * secs) - cosf(4 * secs)) + 7;

    leg_position return_pos = {
        .pos_x = x,
        .pos_y = y
    };

    return return_pos;
}