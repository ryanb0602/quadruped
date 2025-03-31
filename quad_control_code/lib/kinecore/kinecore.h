#ifndef KINECORE_H
#define KINECORE_H

//all angles are radians

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

//structure for all leg deltas
struct leg_deltas {
    float a_vals[4];
    float b_vals[4];
};

//defines leg
class leg {

    public:
        
        //sets what the ideal angles should currently be
        void set_ideal_theta(leg_thetas thetas);

        //gets the current ideal thetas
        leg_thetas ideal_thetas();

        //gets adjusted ideal thetas
        leg_thetas adj_ideal_thetas();


        //sets the ideal xy
        //false if pos is unreachable
        bool set_ideal_x_y(leg_position position);

        //gets the current ideal end effector xy position
        leg_position ideal_pos();

        //gets the current real end effector xy position
        leg_position real_pos();

        //set seglen
        void set_seg_len(float len);

        void set_ident(int id);

    private:
        leg_position forward_kin(float angle_a, float angle_b);
        float ideal_a;
        float ideal_b;

        float seg_lens;

        //here for now, will be used for stabilization and hip y value compensation
        float stable_offset_a;
        float stable_offset_b;

        float hip_offset_a;
        float hip_offset_b;

        int ident;
};

#include <paracore.h>

//class for managing all kinematic calcs
class kinecore {

    public:
        kinecore();
        //set leg segment lengths for all legs in meters
        void set_segment_lens(float len);

        void bind_parametric(int leg_n, parametric *function);

        void update_paras();

        leg_position leg_x_y(int leg_n);

        leg_thetas leg_thetas_vals(int leg_n);

    private:
        leg leg_arr[4];
        para_handler parametric_handler;
};

#endif