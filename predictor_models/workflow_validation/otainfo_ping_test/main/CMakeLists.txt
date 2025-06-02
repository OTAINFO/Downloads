# set(OBJ_FILES
#    ${CMAKE_CURRENT_SOURCE_DIR}/model.c.obj 
#    ${CMAKE_CURRENT_SOURCE_DIR}/otainfo_predictor.c.obj 
# )

# Register as a component
idf_component_register(
    SRCS main.cc 
    PRIV_REQUIRES esp_wifi nvs_flash lwip esp_netif
    INCLUDE_DIRS "../components/external_lib" "$ENV{IDF_PATH}/components/esp_wifi/include" "$ENV{IDF_PATH}/components/nvs_flash/include" "$ENV{IDF_PATH}/components/lwip/include/apps/"
                       "$ENV{IDF_PATH}/components/esp_netif/include" "$ENV{IDF_PATH}/components/lwip/include/apps/ping")

