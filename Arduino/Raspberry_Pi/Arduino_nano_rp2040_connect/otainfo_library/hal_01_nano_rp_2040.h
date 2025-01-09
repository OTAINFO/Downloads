//
/// Copyright (c) 2024 OTAinfo, Inc. USA, All rights are reserved.
//

#include "api/IPAddress.h"
#include <sys/_stdint.h>
#include <string.h>

#ifndef hal_01_nano_rp_2040_H
#define hal_01_nano_rp_2040_H



typedef struct {

      String url;
      uint16_t url_port;
      String protocol;
      String header;
      String status;
      String method;
      String uri;
      String payload;
      String delimiter;
      String host;
      String raw_response;
      int response_status;
  } HTTPCallRequirements;


typedef struct {
  String name;

}GSMConnData;

typedef struct {
  String name;

} BLEConnData;

typedef struct {
  String name;
  String ssid;
  String password;
  long rssi;
  int encryptionType;
  IPAddress ipaddress;
  byte macaddress[6];
  long time;


}WIFIConnData;

typedef struct {
 GSMConnData gsm;
 BLEConnData ble;
 WIFIConnData wifi;
 uint8_t mrssi;
 uint16_t mdata;
 uint8_t mbatt;
 String urls;

} ConnData;

typedef struct {
  float x_val;
  float y_val;
  float z_val;
}AcclerometerData;

typedef struct{
  float Gx;
  float Gy;
  float Gz;
  int sample_rate_hz;
} GyroscopeData;

//void createConnection(ConnData* conndata, HTTPCallRequirements* httpdata);

typedef struct {
     String name;
     String meduim;
     String rx_pin;
     String tx_pin;
     String ce_pin;
     String clk_pin;
     String rst_pin;
     String portname;
     int datareadfrequency;
     bool initialized;
     String recentdata;
     String log;
} SensorData;

//Security 

typedef struct {

  String name;
  uint8_t security;
  String config;
  bool permission_hash;
  bool access_root;
  bool generate_signatures;
  bool read_info;
  bool access_model_space;
  
} scoproccesor;

//
int load_wifidata(WIFIConnData wd, int pin);
int connectwifi();
IPAddress getipaddress();
AcclerometerData getAccelerometerData() ;
void makeHttpCall(HTTPCallRequirements *httpdata);
GyroscopeData getGyroscopeData();
int getTemperature();

#endif
