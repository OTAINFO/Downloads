<b>Learn how to turn this model into a device-agnostic process-success predictor deployable on any CPU or MCU with TensorFlow Lite support</b> <br>

Step 1:
```
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"   
#include "tensorflow/lite/micro/micro_interpreter.h" 
#include "tensorflow/lite/micro/system_setup.h" 
#include "tensorflow/lite/schema/schema_generated.h" 
```

Step2:
```
#include "otainfo_predictor.h"  // Sample below. repleace this with your preditor 
#include "model.h"              // Change this if required else use the same variable 
#include "esp_heap_caps.h"      // Replace this with the library provided by CPU/MPU to get heap stats 
#include "esp_wifi.h"           // Repalce with with the wifi library provided from wifi manufacturer or OS to get Wifi stats 
```

Step2 - Sample for otainfo_predictor.h
```
#ifndef OTAINFO_PREDICTOR_MAIN_FUNCTIONS_H_ 
#define OTAINFO_PREDICTOR_MAIN_FUNCTIONS_H_  
// Expose a C friendly interface for main functions. 
#ifdef __cplusplus 
extern "C" {  
#endif   
typedef struct {  
    int score;  // Inferense returns this score
    bool inadequate_on_cputemperature;  //Compute this plus next three attributes and take corrective action, from edge, if needed
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
#endif 
```


Step 3: OTAinfo_predictor.cc Change name to whatever you want to call <br>
(Required features listed here)
```

namespace { 
const tflite::Model* model = nullptr; 
tflite::MicroInterpreter* interpreter = nullptr; 
TfLiteTensor* input = nullptr; 
TfLiteTensor* output = nullptr; 
int inference_count = 0; 

constexpr int kTensorArenaSize = 4000; 
uint8_t tensor_arena[kTensorArenaSize];
multi_heap_info_t heap_info;
wifi_ap_record_t wifi_info;
float battery_level;
float heap_largest_free_block ;
float free_heap_size ;
float wifi_rssi;
float cpu_temperature; 
float is_charging;
} 


int model_setup() {

  model = tflite::GetModel(g_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    MicroPrintf("Model provided is schema version %d not equal to supported "
                "version %d.", model->version(), TFLITE_SCHEMA_VERSION);
    return -1;
  }
  
  // Pull in only the operation implementations we need.
  static tflite::MicroMutableOpResolver<10> resolver;
  if (resolver.AddFullyConnected() != kTfLiteOk) {
    return -2;
  }
  if(resolver.AddRelu() != kTfLiteOk) {
    return -3;
  }
  if(resolver.AddLogistic() != kTfLiteOk) {
    return -4;
  }
   
  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    MicroPrintf("AllocateTensors() failed");
    return -5;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);

  // Keep track of how many inferences we have performed.
  inference_count = 0;
  return 0;
}

int predict(predictor_reply *preply){
// This is the sequence. The application needs to load realtime values in its respective vairables using native functions.
//["battery_level","heap_largest_free_block", "free_heap_size", "wifi_rssi", "cpu_temperature", "is_charging" ]

//make functions using native library to load these 6 variables.
  input->data.f[0] = battery_level;  
  input->data.f[1] = heap_largest_free_block;
  input->data.f[2] = free_heap_size;
  input->data.f[3] = wifi_rssi;
  input->data.f[4] = cpu_temperature;
  input->data.f[5] = is_charging;
  
  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    MicroPrintf("Invoke failed \n");
    return -1;
  }
  int score = output->data.int8[0];
  preply->score = score;

}
```

Refer to [main.cc](https://github.com/OTAINFO/Downloads/blob/main/predictor_models/ESP-IDF/esp32/main/main.cc) on how to call your predictor

