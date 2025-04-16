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

## http(s) callback function

In sample/main/main.c function my_http_callback will fetch the response and status code. The repose is limited to 1024 bytes.

## What does OTAinfo collect on OTAinfo cloud after each API call for this version

Data: {"deviceid":"EC:64:C9:90:A7:AC","devicetype":{"make":"ESP32","model":1,"features":50,"cores":2,"revision":301,"mac":"EC:64:C9:90:A7:AC"}}


## Sample output ( may differ based on usecase )

I (6108) WiFi: Response in calling app: 65535

I (6108) OPC: Partition Label: nvs

I (6118) OPC: Partition Type: Data

I (6118) OPC: partition subtype:  0x00000002

I (6118) OPC: partition address: 0x00009000

I (6128) OPC: Partition size: 16384 bytes

I (6128) OPC: Partition Label: otadata

I (6138) OPC: Partition Type: Data

I (6138) OPC: partition subtype:  0x00000000

I (6138) OPC: partition address: 0x0000e000

I (6148) OPC: Partition size: 8192 bytes

I (6148) OPC: Partition Label: app0

I (6148) OPC: Partition Type: App

I (6158) OPC: APP partition found...

I (6158) OPC: partition subtype:  0x00000010

I (6158) OPC: partition address: 0x00010000

I (6168) OPC: Partition size: 1310720 bytes

I (6168) OPC: Partition Label: app1

I (6178) OPC: Partition Type: App

I (6178) OPC: APP partition found...

I (6178) OPC: 

OTA updates are possible

I (7598) HTTPS_CALL: Payload: {"deviceid":"EC:64:C9:90:A7:AC","devicetype":

{"make":"ESP32","model":1,"features":50,"cores":2,"revision":301,"mac":"EC:64:C9:90:A7:AC"}}

I (8508) HTTPS_CALL: HTTP_EVENT_ON_CONNECTED

I (8518) HTTPS_CALL: HTTP_EVENT_HEADER_SENT

I (8828) HTTPS_CALL: HTTP_EVENT_ON_HEADER, key=Allow, value=GET, POST, HEAD, OPTIONS

I (8828) HTTPS_CALL: HTTP_EVENT_ON_HEADER, key=Content-Type, value=application/json

I (8838) HTTPS_CALL: HTTP_EVENT_ON_HEADER, key=Date, value=Wed, 16 Apr 2025 05:36:49 GMT

I (8848) HTTPS_CALL: HTTP_EVENT_ON_HEADER, key=Server, value=WSGIServer/0.1 Python/2.7.18

I (8848) HTTPS_CALL: HTTP_EVENT_ON_HEADER, key=Vary, value=Accept

I (8858) HTTPS_CALL: HTTP_EVENT_ON_HEADER, key=X-Frame-Options, value=SAMEORIGIN

I (8868) HTTPS_CALL: HTTP_EVENT_ON_HEADER, key=Content-Length, value=43

I (8868) HTTPS_CALL: HTTP_EVENT_ON_HEADER, key=Connection, value=keep-alive

I (8878) HTTPS_CALL: HTTP_EVENT_ON_DATA, len=43

I (8878) HTTPS_CALL: HTTP_EVENT_ON_FINISH

I (8888) HTTPS_CALL: Full Response:{"message":"Record created","success":true}


I (8888) HTTPS_CALL: status of /hb: 200

I (14188) GRP: Currently running partition: app0 at 0x10000

I (14188) main_task: Returned from app_main()



# Production version

## OTAinfo Analytics

### Metrics:

1. Customer defined
2. Update progress
3. Operation success
4. Resources usage
5. Device security data
6. Pre and Post update test data
7. Environment based performance data like location, connectivity strength, weather etc.

### AI based ticketing and automated issue fixing

1. Metrics' data is processed through an AI engine to generate issue tickets
2. These tickets are clubbed together on basis of common issues
3. Analyzed and a fix is generated (manual/automatic) and applied
4. Cloud to device 1-1 connectivity possible under certain device environments

### Secured OTA Updates for firmware, data and configuration files

1. For security OTAinfo uses Uptane standard
2. Finds the next update, prepares a sequence (if multiple chips need to be updated) & applies it
3. Runs post update test to confirm success before turning it to the new version
4. Rolls back if update fails


# HTTP call data explained


 HTTPCallRequirements httpdata = {
 
          .url =  "http://<url>:8000/", (url with port)
          
          .url_port = "8000",  (specifiy port again)
          
          .protocol = "http",  (http/https)
          
          .header = {
          
            {.key = "Content-Type",
            
             .value = "application/json"},
             
            {.key = "X-Request-Source",
            
             .value = "ESP-IDF"},
             
            {.key = "-",    (takes maximum of 5 headers. If giving less than five, add this as the last key/value)
            
             .value = "-"}},  
             
        .status = 0,
        
        .method = "GET",
        
        .uri = "api-token-auth/",  (uri must not start with a '/')
        
        .payload = "{\"username\" : \"\", \"password\" : \"\"}",
        
        .retries = 2,
        
        .response = "",
        
     };




 







