#include <Arduino.h>

#ifndef KINECORE_H
#define KINECORE_H

class kinecore {

    public:
        void stabilize();
    private:
        void move_one_leg(int leg, float d_a, float d_b);
        
        leg leg_arr[4];

};

class leg {

    public:
        
        void set_position();

    private:

        float angle_a;
        float angle_b;
        float real_a;
        float real_b;

};

#endif