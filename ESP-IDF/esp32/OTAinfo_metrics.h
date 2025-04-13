#ifndef OTAINFO_METRICS_H
#define OTAINFO_METRICS_H

#define MAX_KEY_LEN 8  // Maximum length of a header key
#define MAX_VALUE_LEN 64 
typedef struct {
     char key[MAX_KEY_LEN];
     char metric[MAX_VALUE_LEN];
} SingleMetric;

enum MetricKey {
    WIFI_STATUS,
    OTAINFO_LOGIN_STATUS,
    CALL_TIME,
    CPU_USAGE,
    MEMORY_USAGE_BEFORE,
    MEMORY_USAGE_DURING,
    MEMORY_USAGE_AFTER,
    ERROR_FOR_TICKET,

};

//total: 616 bytes 
typedef struct {
     char* mac;  //18
     char* wifi_mac; //18
     char* model;  // 2
     char* make;  //2
     SingleMetric singlemetric[8]; //576
} OTAinfo_metric;

#endif //OTAINFO_METRICS
