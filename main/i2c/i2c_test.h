#ifndef I2C_TEST_H
#define I2C_TEST_H


#include <driver/i2c.h>
#include <esp_log.h>

#define I2C_MASTER_SDA_IO    8   // SDA GPIO8
#define I2C_MASTER_SCL_IO    9   // SCL GPIO9
#define I2C_MASTER_NUM       I2C_NUM_0
#define I2C_MASTER_FREQ_HZ   100000
#define I2C_TIMEOUT_MS       1000

void i2c_scan();
void setI2CConfig();

#endif // I2C_TEST_H