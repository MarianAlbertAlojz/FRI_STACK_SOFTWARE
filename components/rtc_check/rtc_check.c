#include <stdbool.h>
#include "soc/rtc.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "rtc_check.h"

static const char *TAG = "RTC_CHECK";

//__attribute__((constructor)) // Constructor function to run before main()
void check_32k_xtal(void)
{
    rtc_clk_32k_enable(true); // Enable the 32KHz external crystal
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Wait for the crystal to stabilize

    // Check if the 32KHz external crystal is being used as the RTC slow clock
    rtc_slow_freq_t slow_clk_src = rtc_clk_slow_freq_get();

    if (slow_clk_src == RTC_SLOW_FREQ_32K_XTAL) {
        ESP_LOGI(TAG, "32KHz crystal IS being used as the RTC slow clock.");
    } else {
        ESP_LOGI(TAG, "32KHz crystal is NOT being used. Current clock source: %d", slow_clk_src);
    }
}
