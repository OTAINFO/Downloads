# Reduce GTM time for Espressif products

Use development tools from OTAinfo for internal testing. [Contact us](https://join.slack.com/t/hal-fpo6396/shared_invite/zt-2swttq21s-IBozsESCoDnMt2N3QYRKRg)
on slack for production release of these libraries.


## Environment: 

ESP-IDF version  v5.5-dev-2375-g1f46216a72-dirty

Competible with c only 

CPUs: 

      esp32

      esp32c2 
      
      esp32c3 
      
      esp32c6 
      
      esp32s2
      
      esp32s3


## OTAinfo libraries

1. OTAinfo.h ( OTA updates )
2. OTAinfo_comm.h (Makeing REST API calls on Wifi)
3. OTAinfo_metrics.h (sending heartbeat to OTAinfo cloud)

## How can I integrate with my code?

### Pre-requisites

ESP-IDF version  v5.5-dev-2375-g1f46216a72-dirty

idf.py set-target [esp32|esp32c2|esp32c3|esp32c6|esp32s2|esp32s3]

idf.py menuconfig 

(a) Serial flasher config  --> Flash Size (2MB) --> select 4MB (for OTA updates)


(b) Partition table --> Partition table (Single factory app, no OTA) --> (X) Custom partition table CSV
    The Partitoion table option must show the (partions.csv) in second line.

### Use the sample code 

Navigate to examples/esp32/sample (directory)

Copy the sample directory in your workspace

If using esp32, no change is required except running idf.py menuconfig (listed in pre-requisites) & configuring flash and partition

#### Not using esp32

Step 1: idf.py set-target <espxxxx>

Step 2: copy OTAinfo.c.obj, OTAinfo_comm.c.obj, OTAinfo.h, OTAinfo_comm.h, OTAinfo_metrics.h from relevant Espressif cpu folder to sample/components/external_lib/

Step 3: idf.py menuconfig to set flash and partition (listed in pre-requisites)

Step 4: idf.py build

Step 5: idf.py flash

Step 6: idf.py monitor


## Final integration:

Follow the main.c code to call respective functions from your application code. 


 







