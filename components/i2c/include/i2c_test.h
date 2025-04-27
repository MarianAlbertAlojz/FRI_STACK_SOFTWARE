#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_MASTER_SDA_IO    8   // 8-SDA 
#define I2C_MASTER_SCL_IO    9   // 9-SCL 
#define I2C_MASTER_NUM       I2C_NUM_0
#define I2C_MASTER_FREQ_HZ   100000
#define I2C_TIMEOUT_MS       1000

void i2c_scan();
esp_err_t setI2CConfig();

#ifdef __cplusplus
}
#endif