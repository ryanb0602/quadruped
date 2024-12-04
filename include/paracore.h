#include <kinecore.h>

class parametric {
    public:
        //set the function
        void set_function(leg_thetas (*function)(int t));

        //set update rate in times per second
        void set_update_rate(int rate);

        //pull the update rate
        int get_update_rate();

        //set runtime in millis
        void set_runtime(int t);

        int get_runtime();

        leg_thetas get_current_vals(int t);

    private:
        leg_thetas (*function)(int t);
        int update_rate = 20;
        int runtime;

};