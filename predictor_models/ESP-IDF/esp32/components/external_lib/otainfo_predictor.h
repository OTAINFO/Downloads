#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_OTAINFO_PREDICTOR_MAIN_FUNCTIONS_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_OTAINFO_PREDICTOR_MAIN_FUNCTIONS_H_

// Expose a C friendly interface for main functions.
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    
    int score;
    bool inadequate_on_cputemperature;
    bool insufficient_on_lbs;
    bool insufficient_freeheap;
    bool less_network_coverage;   
} predictor_reply;

int model_setup();
int predict(predictor_reply *preply);
void setCharging(bool charging_option);
void setWifi(bool wifi);

#ifdef __cplusplus
}
#endif

#endif //TENSORFLOW_LITE_MICRO_EXAMPLES_OTAINFO_PREDICTOR_MAIN_FUNCTIONS_H_