.bin file can be deployed directly on ESP32 to check the execution

To test the sample code, reduce heap before calling the predict function. This will result in low score and heap alert.

The sample code monitors heap_largest_free_block, free_heap_size and wifi_rssi (if connected).

It will give individual warning based on which of these 3 parameters are low.

To use the raw model, checkout [esp32-process-success-predictor](https://huggingface.co/otainfo/esp32-process-success-predictor/blob/main/README.md)
