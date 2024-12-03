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

//class for managing all kinematic calcs
class kinecore {

    public:
        //gets all delta angles for motion core
        leg_deltas all_leg_deltas();

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

        //gets adjusted ideal thetas
        leg_thetas adj_ideal_thetas();

        //gets the current real thetas
        leg_thetas real_thetas();

        //sets the ideal xy
        //false if pos is unreachable
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

        //here for now, will be used for stabilization and hip y value compensation
        float stable_offset_a;
        float stable_offset_b;

        float hip_offset_a;
        float hip_offset_b;
};

#endif