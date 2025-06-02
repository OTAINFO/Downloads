idf_component_register(SRCS "wifi_rssi_mapper.c"
                       PRIV_REQUIRES esp_wifi nvs_flash
                    INCLUDE_DIRS "." "$ENV{IDF_PATH}/components/esp_wifi/include" "$ENV{IDF_PATH}/components/nvs_flash/include")
