#include "twai_test.h"

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/twai.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define CAN_TX_GPIO GPIO_NUM_14 // TX pin
#define CAN_RX_GPIO GPIO_NUM_13  // RX pin

static const char *TAG = "TWAI_Example";
//speeds that work tested 5,10,20,50,100,125,250,500,800,1000 kbps
// speeds not tested 12.5, 16, 25
// Configure message to transmit
twai_message_t message = {
    // Message type and format settings
    .extd = 1,              // Standard vs extended format
    .rtr = 0,               // Data vs RTR frame
    .ss = 0,                // Whether the message is single shot (i.e., does not repeat on error)
    .self = 0,              // Whether the message is a self reception request (loopback)
    .dlc_non_comp = 0,      // DLC is less than 8
    // Message ID and payload
    .identifier = 0xAAAA,
    .data_length_code = 4,
    .data = {0, 1, 2, 3},
};

void twai_config(void)
    {
    
    // Initialize configuration structures using macro initializers
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_14, GPIO_NUM_13, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    // Install TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) {
        printf("Driver installed\n");
    } else {
        printf("Failed to install driver\n");
        return;
    }

    // Start TWAI driver
    if (twai_start() == ESP_OK) {
        printf("Driver started\n");
    } else {
        printf("Failed to start driver\n");
        return;
    }

}

void twai_loop_test(void *arg)
{
    // Initialize TWAI configuration
    twai_config();

    // Infinite loop to keep the task running
    // Queue message for transmission
    while (1)
    {
        if (twai_transmit(&message, pdMS_TO_TICKS(1000)) == ESP_OK) {
            printf("Message queued for transmission\n");
        } else {
            printf("Failed to queue message for transmission\n");
            
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}

void twai_loopback_test(void *arg) {
    twai_config();
    
    while (1) {
        // Receive message
        twai_message_t received_msg;
        if (twai_receive(&received_msg, pdMS_TO_TICKS(1000)) == ESP_OK) {
            printf("Received message with ID 0x%lX: [%d, %d, %d, %d]\n",
                   received_msg.identifier,
                   received_msg.data[0], received_msg.data[1],
                   received_msg.data[2], received_msg.data[3]);
        } else {
            printf("No message received\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}
