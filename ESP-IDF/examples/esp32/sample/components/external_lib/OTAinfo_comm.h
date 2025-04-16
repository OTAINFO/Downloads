#ifndef OTAINFO_COMM_H
#define OTAINFO_COMM_H

#include "freertos/queue.h"
#define CHUNK_MAX_LEN 512

extern QueueHandle_t chunk_queue;

#define MAX_KEY_LEN 50  // Maximum length of a header key
#define MAX_VALUE_LEN 100 // Maximum length of header value

extern const char root_cert_pem_start[];

typedef void (*http_response_callback_t)(const char *response, int status_code);
  typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
} HttpHeader;

  typedef struct {
      char* url;  
      char* url_port;
      char* protocol;
      HttpHeader header[5];
      uint16_t status;
      char* method;
      char* uri;
      char* payload;
      char* response;
      const char *certificate;
      uint8_t retries; 
  } HTTPCallRequirements;

typedef enum {
    WIFI_DISCONNECTED,
    WIFI_CONNECTING,
    WIFI_CONNECTED
} WifiStatus;


void starttask(WifiStatus current_status, HTTPCallRequirements *httpdata, http_response_callback_t cb);


#endif
