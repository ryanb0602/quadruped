#include <pindefs.h>
#include <vector>
#include <Adafruit_INA219.h>
#include <Wire.h>
#include <string>

#ifndef MUXED_INA_H
#define MUXED_INA_H

class muxed_ina {
    public:
        muxed_ina(int sda, int scl, int addr, int num_channels, std::vector<float*> outputs);
        ~muxed_ina();

        //frequency is the frequency at which each channel must be polled
        void begin(int frequency);

        void stop();

        //to be called every loop iteration
        void update();

    private:
        void move_mux(int channel);

        int sda;
        int scl;
        int addr;
        int num_channels;
        std::vector<float*> outputs;

        Adafruit_INA219 ina;
        TwoWire* wire;

        bool running;

        int period;
        int current_channel;
        unsigned long last_update;
};

#endif