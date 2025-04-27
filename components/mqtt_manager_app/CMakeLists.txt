idf_component_register(
    SRCS "mqtt_manager_app.c"
    INCLUDE_DIRS "include"
    REQUIRES mqtt esp_event driver
)
