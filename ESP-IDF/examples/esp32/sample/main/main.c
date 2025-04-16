/* 
   (c) 2025 OTAinfo, Inc. All rights reserved. 
   To be used only for feature test purpose.
*/

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "regex.h"
#include "OTAinfo.h"
#include "OTAinfo_comm.h"

#define WIFI_TIMEOUT_MS (15000) // 15 seconds timeout
#define MAX_RETRY 5
static EventGroupHandle_t wifi_event_group;
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
static const char *TAG = "WiFi";
static int retry_count = 0;
WifiStatus current_status = WIFI_DISCONNECTED;
#define CHUNK_SIZE 512
QueueHandle_t chunk_queue;


static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        if (retry_count < MAX_RETRY)
        {
            esp_wifi_connect();
            retry_count++;
            ESP_LOGI(TAG, "Retrying Wi-Fi connection... (%d/%d)", retry_count, MAX_RETRY);
        }
        else
        {
            xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
        }
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "Connected! IP Address: " IPSTR, IP2STR(&event->ip_info.ip));
        retry_count = 0;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}
void connect(char WIFI_SSID[], char WIFI_PASS[])
{

    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "",
            .password = "",
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Waiting for Wi-Fi connection (Timeout: %d ms)...", WIFI_TIMEOUT_MS);

    // Wait for connection with timeout
    EventBits_t bits = xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE, pdMS_TO_TICKS(WIFI_TIMEOUT_MS));

    if (bits & WIFI_CONNECTED_BIT)
    {
        ESP_LOGI(TAG, "Wi-Fi Connected Successfully");
        current_status = WIFI_CONNECTED;
    }
    else if (bits & WIFI_FAIL_BIT || bits == 0)
    { // Timeout case
        ESP_LOGW(TAG, "Wi-Fi connection failed or timed out!");
        current_status = WIFI_DISCONNECTED;
        esp_wifi_stop(); // Stop Wi-Fi if timeout occurs
    }
}
void my_http_callback(const char *data, int code) {
    printf("Got response: %s with status: %d\n", data, code);
}

void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);

    char ssid[] = "test_iot";
    char pass[] = "Test123$56";
    connect(ssid, pass);
    vTaskDelay(pdMS_TO_TICKS(3000));
    check_panic();
    can_rollback();
     HTTPCallRequirements httpdata = {
          .url =  "http://<url>:8000/",
          .url_port = "8000",
          .protocol = "http",
          .header = {
            {.key = "Content-Type",
             .value = "application/json"},
            {.key = "X-Request-Source",
             .value = "ESP-IDF"},
            {.key = "-",
             .value = "-"}},
        .status = 0,
        .method = "GET",
        .uri = "/api-token-auth/",
        .payload = "{\"username\" : \"\", \"password\" : \"\"}",
        .retries = 2,
        .response = "",
     };
   
    starttask(current_status, &httpdata,  my_http_callback);
    ESP_LOGI(TAG, "Response in calling app: %d", httpdata.status);
    if (ota_partition_check())
    {
        get_running_partition();
        //start_ota("url"); // with valid url including the file name of update, this function will start update if conditions are met.
    }

}

