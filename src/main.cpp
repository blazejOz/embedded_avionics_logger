#include "pico/stdlib.h"
#include "FatFsSd.h"
#include "imu/MPU6050.h"
#include "recorder/Recorder.h"
#include "utils/Utils.h"
#include "pinout.h"

int main() {
    stdio_init_all();
    sleep_ms(3000); 
    
    
    Utils::init(START_BTN_PIN, GREEN_LED_PIN, RED_LED_PIN);
    MPU6050 mpu(MPU_I2C_PORT, MPU_SDA_PIN, MPU_SCL_PIN); 
    Recorder recorder(SD_SPI_PORT, SD_MISO_PIN, SD_MOSI_PIN, SD_SCK_PIN, SD_CS_PIN);

    while(true){
        if(Utils::is_button_clicked()){
            Utils::turnOn_green();
            recorder.start_recording();
            printf("\n--- Starting Flight Recorder ---\n");
            break;
        }
        sleep_ms(50);
    }

    Gyro_t current_gyro;
    Accel_t current_accel;
    while(true) {
        if(Utils::is_button_clicked()){
            Utils::turnOff_green();
            recorder.stop_recording();
            printf("\n--- Stoping Flight Recorder ---\n");
            break;
        }

        mpu.getGyro(&current_gyro);
        mpu.getAccel(&current_accel);
        recorder.log_data(current_gyro, current_accel);

        printf("Logged: Gyro X:%d Y:%d Z:%d Accel X:%d Y:%d Z:%d \n", current_gyro.x, current_gyro.y, current_gyro.z , current_accel.x, current_accel.y, current_accel.z) ;

        sleep_ms(50); 
    }

}
   