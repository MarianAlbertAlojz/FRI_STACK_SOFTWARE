
#include <stdio.h>

#include "esp_log.h"
#include "esp_system.h"
#include "soc/rtc.h"
#include "driver/rtc_io.h"
#include <inttypes.h>
#include "esp_private/esp_clk.h" 
#include "esp32s3/rtc.h"
#include "esp32s3/rom/rtc.h"
#include "wifi_manager_app.h"
#include "mqtt_manager_app.h"
void app_main(void)
{
    wifi_init();         // Connect to Wi-Fi (blocks until connected)
    mqtt_app_start();   // Start MQTT client
    //twai_loop_test(NULL); // Start TWAI loop test
}
    
    

