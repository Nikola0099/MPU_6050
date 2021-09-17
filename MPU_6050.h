#include <stdint.h>
#include <stm32f1xx_hal_conf.h>
#include <stm32f1xx_it.h>
#include <string.h>

uint16_t DevAddress =  0b11010010; // Adresa uredjanja (nadjena u dokumentaciji)
uint16_t DevAddressRead =  0b11010011;
I2C_HandleTypeDef hi2c1;

void sensorSetup(uint8_t External_Synch_Set, uint8_t Digital_Low_Pass_Filter, uint8_t X_Gyro_Self_test, uint8_t Y_Gyro_Self_test, uint8_t Z_Gyro_Self_test, uint8_t Gyro_Full_Scale_Range,
                 uint8_t X_Accel_Self_test, uint8_t Y_Accel_Self_test, uint8_t Z_Accel_Self_test, uint8_t Accel_Full_Scale_Range, uint8_t Device_Reset, uint8_t Sleep, uint8_t Cycle,
                 uint8_t Temp_Disable, uint8_t Clock_Select, uint8_t Sample_Rate_Divider)
{

    uint8_t DataBuffer[5];
    uint8_t powerManagment7, powerManagment6, powerManagment5, powerManagment3, powerManagment2_0, powerManagment;

    switch(Device_Reset)
    {
        case 0: powerManagment7 = 0; break;
        case 1: powerManagment7 = 128; break;
            default: powerManagment7 = 0;
    }

    switch(Sleep)
    {
        case 0: powerManagment6 = 0; break;
        case 1: powerManagment6 = 64; break;
            default: powerManagment6 = 0;
    }

    switch(Cycle)
    {
        case 0: powerManagment5 = 0; break;
        case 1: powerManagment5 = 32; break;
            default: powerManagment5 = 32;
    }

    switch(Temp_Disable)
    {
        case 0: powerManagment3 = 0; break;
        case 1: powerManagment3 = 128; break;
            default: powerManagment3 = 0;
    }

    powerManagment2_0 = Clock_Select;

    powerManagment =  powerManagment7 | powerManagment6 | powerManagment5 | powerManagment3 | powerManagment2_0;
    powerManagment = 1;

    uint8_t powerManagmentSleep[2] = {107, 0b00000000};
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, powerManagmentSleep, 2, HAL_MAX_DELAY);

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &powerManagmentSleep[0], 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    HAL_Delay(1000);



    uint8_t powerManagmentSet[2] = {107, powerManagment};
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, powerManagmentSet, 2, HAL_MAX_DELAY);

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &powerManagmentSet[0], 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    

    uint8_t config5_3, config2_0, config;

    switch(External_Synch_Set)
    {
        case 0: config5_3 = 0; break;
        case 1: config5_3 = 8; break;
        case 2: config5_3 = 16; break;
        case 3: config5_3 = 24; break;
        case 4: config5_3 = 32; break;
        case 5: config5_3 = 40; break;
        case 6: config5_3 = 48; break;
        case 7: config5_3 = 56; break;
            default: config5_3 = 0;
    }

    config2_0 = Digital_Low_Pass_Filter;

    config = config5_3 | config2_0;

    uint8_t configSet[2] = {26, config};
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, configSet, 2, HAL_MAX_DELAY);

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &configSet[0], 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);

    
    uint8_t sampleRateDivider = Sample_Rate_Divider;
    uint8_t sampleRateDividerSet[2] = {25, sampleRateDivider};
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, sampleRateDividerSet, 2, HAL_MAX_DELAY);

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &sampleRateDividerSet[0], 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);


    uint8_t gyroConfig7, gyroConfig6, gyroConfig5, gyroConfig4_3, gyroConfig;

    switch(X_Gyro_Self_test)
    {
        case 1: gyroConfig7 = 128; break;
            default: gyroConfig7 = 0;
    }

    switch(Y_Gyro_Self_test)
    {
        case 1: gyroConfig6 = 64; break;
            default: gyroConfig6 = 0;
    }

    switch(Z_Gyro_Self_test)
    {
        case 1: gyroConfig5 = 32; break;
            default: gyroConfig5 = 0;
    }

    switch(Gyro_Full_Scale_Range)
    {
        case 0: gyroConfig4_3 = 0; break;
        case 1: gyroConfig4_3 = 8; break;
        case 2: gyroConfig4_3 = 16; break;
        case 3: gyroConfig4_3 = 24; break;
            default: gyroConfig4_3 = 0;
    }

    gyroConfig = gyroConfig7 | gyroConfig6 | gyroConfig5 | gyroConfig4_3;

    uint8_t gyroConfigSet[2] = {27, gyroConfig};
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, gyroConfigSet, 2, HAL_MAX_DELAY);

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &gyroConfigSet[0], 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);


    uint8_t accelConfig7, accelConfig6, accelConfig5, accelConfig4_3, accelConfig;

    switch(X_Accel_Self_test)
    {
        case 1: accelConfig7 = 128; break;
            default: accelConfig7 = 0;
    }

    switch(Y_Accel_Self_test)
    {
        case 1: accelConfig6 = 64; break;
            default: accelConfig6 = 0;
    }

    switch(Z_Accel_Self_test)
    {
        case 1: accelConfig5 = 32; break;
            default: accelConfig5 = 0;
    }

    switch(Accel_Full_Scale_Range)
    {
        case 0: accelConfig4_3 = 0; break;
        case 1: accelConfig4_3 = 8; break;
        case 2: accelConfig4_3 = 16; break;
        case 3: accelConfig4_3 = 24; break;
            default: accelConfig4_3 = 0;
    }

    accelConfig = accelConfig7 | accelConfig6 | accelConfig5 | accelConfig4_3;

    uint8_t accelConfigSet[2] = {28, accelConfig};
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, accelConfigSet, 2, HAL_MAX_DELAY);

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &accelConfigSet[0], 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);



    uint8_t IntPin = 55;
    uint8_t IntPinSet[2] = {55, 0x02};
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, IntPinSet, 2, HAL_MAX_DELAY);

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &IntPinSet[0], 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);

    HAL_Delay(1000);

}