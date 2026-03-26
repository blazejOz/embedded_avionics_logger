#include "Recorder.h"


// GLOBAL STRUCTURES (Required by the no-osFatFS library)
static spi_t _spi_bus = {}; 
static sd_spi_if_t _spi_if = {};
static sd_card_t _sd_card_config = {};

// "GLUE" CODE 
// NEEDED TO WORK WITH no-osFatFS lib
namespace FatFsNs {
    std::vector<SdCard> FatFs::SdCards;
}

extern "C" {
    size_t sd_get_num() { return 1; }
    sd_card_t *sd_get_by_num(size_t num) {
        if (num == 0) return &_sd_card_config;
        return nullptr;
    }
}


// CLASS LOGIC

Recorder::Recorder(spi_inst_t* spi_port, uint miso, uint mosi, uint sck, uint cs) {
    // Fill in the global config structures with the values passed by the user
    _spi_bus.hw_inst = spi_port;
    _spi_bus.miso_gpio = miso;
    _spi_bus.mosi_gpio = mosi;
    _spi_bus.sck_gpio = sck;
    _spi_bus.baud_rate = 12 * 1000 * 1000;
    
    // Default drive strengths
    _spi_bus.set_drive_strength = true;
    _spi_bus.mosi_gpio_drive_strength = GPIO_DRIVE_STRENGTH_12MA;
    _spi_bus.sck_gpio_drive_strength = GPIO_DRIVE_STRENGTH_12MA;

    _spi_if.spi = &_spi_bus;
    _spi_if.ss_gpio = cs;

    _sd_card_config.type = SD_IF_SPI;
    _sd_card_config.spi_if_p = &_spi_if;
    _sd_card_config.use_card_detect = false;

    printf("\n--- RECORDER HARDWARE CONFIGURED ---\n");
    
    // Now actually initialize the driver
    sd_init_driver(); 
    this->card_p = FatFsNs::FatFs::add_sd_card(&_sd_card_config);
}

void Recorder::start_recording() 
{
    this->card_p->mount();

    char filename[20];
    int file_idx = 0;
    FRESULT fr;

    // Loop until we find a filename that DOES NOT exist
    while (true) {
        sprintf(filename, "flight_%03d.csv", file_idx);
        FILINFO fno;
        fr = f_stat(filename, &fno); 
        
        if (fr == FR_NO_FILE) {
            // This name is free
            break; 
        }
        file_idx++;
    }

    fr = file.open(filename, FA_WRITE | FA_OPEN_APPEND);
    if (fr == FR_OK) {
        is_open = true;
        file.puts("Timestamp_ms,GyroX,GyroY,GyroZ,AccelX,AccelY,AccelZ\n");
        file.sync();
        return;
    }
    Utils::handle_error("SD Open Failed");
}

void Recorder::log_data(uint32_t timestamp, const Gyro_t& gyro, const Accel_t& accel) 
{
    if(!is_open) return;

    char buffer[64];
    sprintf(buffer, "%lu, %d, %d, %d, %d, %d, %d\n", timestamp, gyro.x, gyro.y, gyro.z, accel.x, accel.y, accel.z);
    file.puts(buffer);
    file.sync();
}

void Recorder::stop_recording()
{
    if(is_open){
        file.close();
        is_open = false;
        this->card_p->unmount();
        std::cout << "File Closed and unmounted" << std::endl;
    }
}


