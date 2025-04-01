#include <muxed_ina.h>

#include <io_debug_tool.h>


muxed_ina::muxed_ina(int sda, int scl, int addr, int num_channels, std::vector<float*> outputs) {
    this->sda = sda;
    this->scl = scl;
    this->addr = addr;
    this->num_channels = num_channels;
    this->outputs = outputs;

    this->ina = Adafruit_INA219(addr);

    this->ina.setCalibration_16V_400mA();

    this->wire = new TwoWire(0);
}

muxed_ina::~muxed_ina() {
    delete this->wire;
}

void muxed_ina::begin(int frequency) {
    debug_print(MAIN_AND_SUB_FUNCTIONS, "ANALOG MUX INITIALIZED");
    this->wire->begin(this->sda, this->scl);
    this->ina.begin(this->wire);

    int period = 1000 / (frequency * this->num_channels);
    running = true;
}

void muxed_ina::stop() {
    running = false;
}

void muxed_ina::update() {
    unsigned long current_time = millis();

    if (current_time - last_update > period) {
        last_update = current_time;

        current_channel += 1;
        if (current_channel >= num_channels - 1) {
            current_channel = 0;
        }
        move_mux(current_channel);

        *outputs[current_channel] = ina.getBusVoltage_V();

        std::string debug_out = "MUX: CHANNEL READ " + std::to_string(*outputs[current_channel]);
        debug_print(MAIN_SUB_AND_NUMERICAL_DATA, debug_out);

    }   
}

void muxed_ina::move_mux(int channel) {
    std::string debug_out = "MUX: CHANNEL SET TO " + std::to_string(channel);
    debug_print(MAIN_SUB_AND_NUMERICAL_DATA, debug_out);
    bool a0 = channel & 0b0001;
    bool a1 = channel & 0b0010;
    bool a2 = channel & 0b0100;
    bool a3 = channel & 0b1000;

    digitalWrite(MUX_A0, a0);
    digitalWrite(MUX_A1, a1);
    digitalWrite(MUX_A2, a2);
    digitalWrite(MUX_A3, a3);
}