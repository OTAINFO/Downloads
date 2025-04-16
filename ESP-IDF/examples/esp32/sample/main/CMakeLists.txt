idf_component_register(SRCS "main.c"
                     PRIV_REQUIRES esp_wifi nvs_flash esp_http_client app_update esp_app_format esp_bootloader_format bootloader_support esp_partition esp_system log esp_common freertos lwip esp-tls nvs_flash esp_hw_support esp_timer json external_lib
                    INCLUDE_DIRS "." "$ENV{IDF_PATH}/components/app_update/include" "$ENV{IDF_PATH}/components/esp_app_format/include" "$ENV{IDF_PATH}/components/esp_bootloader_format/include" 
                    "$ENV{IDF_PATH}/components/bootloader_support/include"  "$ENV{IDF_PATH}/components/esp_http_client/include"  "$ENV{IDF_PATH}/components/esp_wifi/include" "$ENV{IDF_PATH}/components/esp-tls"
                     "$ENV{IDF_PATH}/components/nvs_flash/include" "$ENV{IDF_PATH}/components/esp_hw_support/include" "$ENV{IDF_PATH}/components/esp_timer/include" "$ENV{IDF_PATH}/components/json/cJSON" "$ENV{IDF_PATH}/examples/wifi/wifi_aware/sample/components/external_lib" "$ENV{IDF_PATH}/components/log/include/" )


