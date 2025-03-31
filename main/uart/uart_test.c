#include "uart_test.h"



static const char *TAG = "UART_ECHO";

void uart_echo_task(void *arg)
{
    uint8_t data[BUF_SIZE];

    while (1) {
        int len = uart_read_bytes(ECHO_UART_PORT_NUM, data, BUF_SIZE, 20 / portTICK_PERIOD_MS);
        if (len > 0) {
            uart_write_bytes(ECHO_UART_PORT_NUM, (const char *) data, len);
            ESP_LOGI(TAG, "Echoed %d bytes", len);
        }
    }
}


void setUartConfig() {
    const uart_config_t uart_config = {
        .baud_rate = ECHO_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    
    uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 0, NULL, 0);

    uart_param_config(ECHO_UART_PORT_NUM, &uart_config);
    uart_set_pin(ECHO_UART_PORT_NUM, GPIO_NUM_43, GPIO_NUM_44, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE); // TXD, RXD
    xTaskCreate(uart_echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
    
}

