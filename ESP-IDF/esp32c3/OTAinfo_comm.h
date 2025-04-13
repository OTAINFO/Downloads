#ifndef OTAINFO_COMM_H
#define OTAINFO_COMM_H

#include "freertos/queue.h"
#define CHUNK_MAX_LEN 512

extern QueueHandle_t chunk_queue;

#define MAX_KEY_LEN 50  // Maximum length of a header key
#define MAX_VALUE_LEN 100 // Maximum length of header value

extern const char root_cert_pem_start[];
// const char root_cert_pem_start[] = R"EOF(
// -----BEGIN CERTIFICATE-----
// MIIEXjCCA0agAwIBAgITB3MSTNQG0mfAmRzdKZqfODF5hTANBgkqhkiG9w0BAQsF
// ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
// b24gUm9vdCBDQSAxMB4XDTIyMDgyMzIyMjYwNFoXDTMwMDgyMzIyMjYwNFowPDEL
// MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEcMBoGA1UEAxMTQW1hem9uIFJT
// QSAyMDQ4IE0wMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALd/pVko
// 8vuM475Tf45HV3BbCl/B9Jy89G1CRkFjcPY06WA9lS+7dWbUA7GtWUKoksr69hKM
// wcMsNpxlw7b3jeXFgxB09/nmalcAWtnLzF+LaDKEA5DQmvKzuh1nfIfqEiKCQSmX
// Xh09Xs+dO7cm5qbaL2hhNJCSAejciwcvOFgFNgEMR42wm6KIFHsQW28jhA+1u/M0
// p6fVwReuEgZfLfdx82Px0LJck3lST3EB/JfbdsdOzzzg5YkY1dfuqf8y5fUeZ7Cz
// WXbTjujwX/TovmeWKA36VLCz75azW6tDNuDn66FOpADZZ9omVaF6BqNJiLMVl6P3
// /c0OiUMC6Z5OfKcCAwEAAaOCAVowggFWMBIGA1UdEwEB/wQIMAYBAf8CAQAwDgYD
// VR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjAdBgNV
// HQ4EFgQUVdkYX9IczAHhWLS+q9lVQgHXLgIwHwYDVR0jBBgwFoAUhBjMhTTsvAyU
// lC4IWZzHshBOCggwewYIKwYBBQUHAQEEbzBtMC8GCCsGAQUFBzABhiNodHRwOi8v
// b2NzcC5yb290Y2ExLmFtYXpvbnRydXN0LmNvbTA6BggrBgEFBQcwAoYuaHR0cDov
// L2NydC5yb290Y2ExLmFtYXpvbnRydXN0LmNvbS9yb290Y2ExLmNlcjA/BgNVHR8E
// ODA2MDSgMqAwhi5odHRwOi8vY3JsLnJvb3RjYTEuYW1hem9udHJ1c3QuY29tL3Jv
// b3RjYTEuY3JsMBMGA1UdIAQMMAowCAYGZ4EMAQIBMA0GCSqGSIb3DQEBCwUAA4IB
// AQAGjeWm2cC+3z2MzSCnte46/7JZvj3iQZDY7EvODNdZF41n71Lrk9kbfNwerK0d
// VNzW36Wefr7j7ZSwBVg50W5ay65jNSN74TTQV1yt4WnSbVvN6KlMs1hiyOZdoHKs
// KDV2UGNxbdoBYCQNa2GYF8FQIWLugNp35aSOpMy6cFlymFQomIrnOQHwK1nvVY4q
// xDSJMU/gNJz17D8ArPN3ngnyZ2TwepJ0uBINz3G5te2rdFUF4i4Y3Bb7FUlHDYm4
// u8aIRGpk2ZpfXmxaoxnbIBZRvGLPSUuPwnwoUOMsJ8jirI5vs2dvchPb7MtI1rle
// i02f2ivH2vxkjDLltSpe2fiC
// -----END CERTIFICATE-----
// )EOF";




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