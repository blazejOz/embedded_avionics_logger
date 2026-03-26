#pragma once

#include <iostream>
#include <vector>
#include <string.h>

#include "../imu/MPU6050.h"
#include "../utils/Utils.h"
#include "FatFsSd.h"


class Recorder {
public:
    Recorder(spi_inst_t* spi_port, uint miso, uint mosi, uint sck, uint cs);
    FatFsNs::SdCard* card_p = nullptr;

    void start_recording();
    void log_data(uint32_t timestamp, const Gyro_t& gyro, const Accel_t& accel);
    void stop_recording();

private:
    FatFsNs::File file; 
    bool is_open = false;

};