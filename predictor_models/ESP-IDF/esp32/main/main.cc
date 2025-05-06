#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "tensorflow/lite/micro/micro_interpreter.h"

#include "otainfo_predictor.h"
predictor_reply pr;
extern "C" void app_main(void) {
  model_setup();
  while (true) {

    predict(&pr);
    // trigger one inference every 500ms
    MicroPrintf("Score: %d", pr.score);
    if (pr.inadequate_on_cputemperature){
        MicroPrintf("Check CPU temperature!!");
    }
    if(pr.insufficient_freeheap) {
        MicroPrintf("Check memory usage");
    }
    if(pr.insufficient_on_lbs){
        MicroPrintf("1.2 MB OTA download needs atleast 32KB of single heap block. For smaller downlaod it may work");
    }
    if(pr.insufficient_freeheap){
        MicroPrintf("1.2MB download over https requires 80-100 kb of heap size");
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}