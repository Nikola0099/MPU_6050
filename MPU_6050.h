#include <stdint.h>
#include <stm32f1xx_hal_conf.h>
#include <stm32f1xx_it.h>
#include <string.h>

/*    PINOUT:
 *  VCC -> 3.3V
 *  GND -> GND
 *  SCL -> B6
 *  SDA -> B7
 *  AD0 -> 3.3V  
 */

uint16_t DevAddress =  0b11010010; // Adresa uredjanja (nadjena u dokumentaciji)
uint16_t DevAddressRead =  0b11010011;
I2C_HandleTypeDef hi2c1;

void sensorSetup(uint8_t External_Synch_Set, uint8_t Digital_Low_Pass_Filter, uint8_t X_Gyro_Self_test, uint8_t Y_Gyro_Self_test, uint8_t Z_Gyro_Self_test, uint8_t Gyro_Full_Scale_Range,
                 uint8_t X_Accel_Self_test, uint8_t Y_Accel_Self_test, uint8_t Z_Accel_Self_test, uint8_t Accel_Full_Scale_Range, uint8_t Device_Reset, uint8_t Sleep, uint8_t Cycle,
                 uint8_t Temp_Disable, uint8_t Clock_Select, uint8_t Sample_Rate_Divider)
{
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

    HAL_Delay(100);

    uint8_t powerManagmentSet[2] = {107, powerManagment};
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, powerManagmentSet, 2, HAL_MAX_DELAY);



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


    
    uint8_t sampleRateDivider = Sample_Rate_Divider;
    uint8_t sampleRateDividerSet[2] = {25, sampleRateDivider};
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, sampleRateDividerSet, 2, HAL_MAX_DELAY);



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


    uint8_t IntPinSet[2] = {55, 0x02};
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, IntPinSet, 2, HAL_MAX_DELAY);

}

void readValue(int16_t *AccelX, int16_t *AccelY, int16_t *AccelZ, int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ, double *RealTemp)
{
    uint8_t DataBuffer[5], niz[5];
    uint8_t Accel_Xout_H = 0x3B;
    uint8_t Accel_Xout_L = 0x3C;
    
    uint8_t Accel_Yout_H = 0x3D;
    uint8_t Accel_Yout_L = 0x3E;
    
    uint8_t Accel_Zout_H = 0x3F;
    uint8_t Accel_Zout_L = 0x40;
    
    uint8_t Gyro_Xout_H = 67;
    uint8_t Gyro_Xout_L = 68;

    uint8_t Gyro_Yout_H = 69;
    uint8_t Gyro_Yout_L = 70;

    uint8_t Gyro_Zout_H = 71;
    uint8_t Gyro_Zout_L = 72;

    uint8_t Temp_Out_H = 65;
    uint8_t Temp_Out_L = 66;
    int16_t Temp;

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Accel_Xout_H, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[0] = DataBuffer[0];
    HAL_I2C_Master_Transmit(&hi2c1, (DevAddress), &Accel_Xout_L, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[1] = DataBuffer[0];
    *AccelX = (uint16_t)niz[0] << 8 | niz[1];

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Accel_Yout_H, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[0] = DataBuffer[0];
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Accel_Yout_L, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[1] = DataBuffer[0];
    *AccelY = (uint16_t)niz[0] << 8 | niz[1];

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Accel_Zout_H, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[0] = DataBuffer[0];
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Accel_Zout_L, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[1] = DataBuffer[0];
    *AccelZ = (uint16_t)niz[0] << 8 | niz[1];

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Gyro_Xout_H, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[0] = DataBuffer[0];
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Gyro_Xout_L, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[1] = DataBuffer[0];
    *GyroX = (uint16_t)niz[0] << 8 | niz[1];

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Gyro_Yout_H, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[0] = DataBuffer[0];
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Gyro_Yout_L, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[1] = DataBuffer[0];
    *GyroY = (uint16_t)niz[0] << 8 | niz[1];

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Gyro_Zout_H, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[0] = DataBuffer[0];
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Gyro_Zout_L, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[1] = DataBuffer[0];
    *GyroZ = (uint16_t)niz[0] << 8 | niz[1];

    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Temp_Out_H, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[0] = DataBuffer[0];
    HAL_I2C_Master_Transmit(&hi2c1, DevAddress, &Temp_Out_L, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, DevAddressRead, DataBuffer, 1, HAL_MAX_DELAY);
    niz[1] = DataBuffer[0];
    Temp = (uint16_t)niz[0] << 8 | niz[1];
    *RealTemp = Temp/340.0 + 36.53;
}