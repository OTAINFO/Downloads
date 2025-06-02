idf_component_register(SRCS "wifi_ping_test.c"
                      PRIV_REQUIRES esp_wifi nvs_flash lwip esp_netif
                      INCLUDE_DIRS "." "$ENV{IDF_PATH}/components/esp_wifi/include" "$ENV{IDF_PATH}/components/nvs_flash/include" "$ENV{IDF_PATH}/components/lwip/include/apps/"
                       "$ENV{IDF_PATH}/components/esp_netif/include" "$ENV{IDF_PATH}/components/lwip/include/apps/ping")

