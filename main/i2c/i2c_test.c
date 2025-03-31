#include "i2c_test.h"

static const char *TAG = "I2C_SCAN";

void i2c_scan()
{
    ESP_LOGI(TAG, "Scanning I2C Bus...");

    for (uint8_t address = 1; address < 127; address++) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);

        esp_err_t err = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(I2C_TIMEOUT_MS));
        i2c_cmd_link_delete(cmd);

        if (err == ESP_OK) {
            ESP_LOGI(TAG, "Device found at 0x%02X", address);
        }
    }
    ESP_LOGI(TAG, "I2C Scan Complete");
}

void setI2CConfig() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_DISABLE,  // using pull up resistors on the board
        .scl_pullup_en = GPIO_PULLUP_DISABLE,  // using pull up resistors on the board
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };

    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}
