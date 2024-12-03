#include <Arduino.h>

#ifndef KINECORE_H
#define KINECORE_H

//struct for easy passing for leg angle data
struct leg_thetas {
    float angle_a;
    float angle_b;
};

//struct for easy passing of leg position data
struct leg_position {
    float pos_x;
    float pos_y;
};

//class for managing all kinematic calcs
class kinecore {

    public:
        //find leg angle deltas based on target x and y positions
        leg_thetas find_leg_deltas_xy(int leg, float targ_x, float targ_y);

        //find leg angle deltas based on target delta positions
        leg_thetas find_leg_deltas_theta(int leg, float targ_a, float targ_b);

        //set leg segment lengths for all legs in meters
        void set_segment_lens(float top_seg, float bottom_seg);

    private:
        leg leg_arr[4];
};

//defines leg
class leg {

    public:
        
        //sets what the ideal angles should currently be
        void set_ideal_theta(leg_thetas thetas);

        //gets the current ideal thetas
        leg_thetas ideal_thetas();

        //gets the current real thetas
        leg_thetas real_thetas();

        //sets the ideal xy
        bool set_ideal_x_y(leg_position position);

        //gets the current ideal end effector xy position
        leg_position ideal_pos();

        //gets the current real end effector xy position
        leg_position real_pos();

    private:
        leg_position forward_kin(float angle_a, float angle_b);
        float ideal_a;
        float ideal_b;
        float real_a;
        float real_b;
        float seg_lens;
};

#endif