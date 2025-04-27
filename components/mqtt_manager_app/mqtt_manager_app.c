#include "mqtt_manager_app.h"

#include <stdint.h>
#include "esp_log.h"
#include "esp_event.h"
#include "mqtt_client.h"

// Later add Kconfig
#define MQTT_BROKER_URI "mqtt://192.168.137.1"

static const char *TAG = "mqtt_manager";
esp_mqtt_client_handle_t mqtt_client;

static void on_mqtt_event(void* _, esp_event_base_t base,
                          int32_t event_id, void* event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    switch (event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT: Connected to broker");
            esp_mqtt_client_subscribe(mqtt_client, "esp32/topic", 0);
            esp_mqtt_client_publish(mqtt_client, "esp32/topic", "Hello from ESP32!", 0, 1, 0);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGW(TAG, "MQTT: Disconnected from broker");
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "Topic: %.*s  Data: %.*s",
                     event->topic_len, event->topic,
                     event->data_len,  event->data);
            break;
        default:
            break;
    }
}

void mqtt_app_start(void)
{
    const esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {
            .address.uri = MQTT_BROKER_URI,
            //.verification.certificate = (const char *)mqtt_eclipseprojects_io_pem_start
        },
    };
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(
        mqtt_client, ESP_EVENT_ANY_ID, on_mqtt_event, NULL);
    ESP_LOGI(TAG, "Starting MQTT…");
    esp_mqtt_client_start(mqtt_client);
}
