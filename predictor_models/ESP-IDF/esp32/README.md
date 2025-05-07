
<b>process_outcome_predictor.bin</b> file can be deployed directly on ESP32 to check the execution

To test the sample code, reduce heap before calling the predict function. This will result in low score and heap alert. To check the wifi alert, take the device away from wifi router. A low wifi signal strength alert will be generated. Note: Wifi must be connected to get this alert. To display alerts on console use idf.py monitor. 

The sample code monitors <b>heap_largest_free_block, free_heap_size and wifi_rssi </b> (if connected).

It will give individual warning based on which of these 3 parameters are low.

To use the <b>raw model</b>, checkout [esp32-process-success-predictor](https://huggingface.co/otainfo/esp32-process-success-predictor/blob/main/README.md)

For more information [contact us](https://join.slack.com/t/hal-fpo6396/shared_invite/zt-2swttq21s-IBozsESCoDnMt2N3QYRKRg)
