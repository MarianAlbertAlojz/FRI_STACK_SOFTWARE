#ifndef UART_TEST_H
#define UART_TEST_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "driver/gpio.h"



#define ECHO_UART_PORT_NUM      UART_NUM_0
#define ECHO_UART_BAUD_RATE     115200
#define ECHO_TASK_STACK_SIZE    2048
#define BUF_SIZE                1024

void uart_echo_task(void *arg);
void setUartConfig();

#endif // UART_TEST_H