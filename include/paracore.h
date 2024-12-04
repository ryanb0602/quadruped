#include <kinecore.h>
#include <chrono>

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

        //get runtime in millis
        int get_runtime();

        //get starttime millis
        int get_starttime();

        //get the last update
        int get_lastupdate();

        //set the last update
        void set_lastupdate(int t);

        leg_thetas get_current_vals(int t);

    private:
        leg_thetas (*function)(int t);
        int update_rate = 20;
        int runtime;
        int start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        int last_update = start_time;
};

struct para_handler_ll {
    parametric current;
    para_handler_ll* ll = nullptr;
    float* a;
    float* b;
};

class para_handler {
    public: 
        //add parametric
        void add_active(parametric to_add, float* a, float* b);

        //update parametrics
        void update_all();

    private:
        int current_time();
        void delete_para(para_handler_ll *ll);
        para_handler_ll *ll;
        para_handler_ll *last;
        int length = 0;
};