#include "hal_01_nano_rp_2040.h"
#include <WiFiNINA.h>
#include <SPI.h>
#include <iostream>
#include "secrets.h"

WIFIConnData wd;
HTTPCallRequirements httpcall;
AcclerometerData acd;
GyroscopeData gs_data;

void setup() {

  wd.name = wd_name;
  wd.ssid = wd_ssid;
  wd.password = wd_password;
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting HAL....");
  load_wifidata(wd, '67091085');
  Serial.println("Connecting to wifi");
  connectwifi();
  if (getipaddress()) {
    Serial.print("Wifi connected");
  }
  acd = getAccelerometerData();
  Serial.print("\nAccelerometer data: ");
  Serial.print("\nsize: ");
  Serial.println(sizeof(acd));
  Serial.print("values:\n   x,     y,     z\n");
  Serial.print(acd.x_val);
  Serial.print(", ");
  Serial.print(acd.y_val);
  Serial.print(", ");
  Serial.print(acd.z_val);
  gs_data = getGyroscopeData();
  Serial.print("\nGyroscope Data:\n");
  Serial.print("values:\n   Gx,    Gy,    Gz\n");
  Serial.print(gs_data.Gx);
  Serial.print(", ");
  Serial.print(gs_data.Gy);
  Serial.print(", ");
  Serial.print(gs_data.Gz);
  Serial.print("\nGyroscope data sample rate: ");
  Serial.print(gs_data.sample_rate_hz);
  Serial.print(" Hz\n");
  int temp = getTemperature();
  Serial.print("\nTemperature(F): \n");
  Serial.print(temp);
  Serial.print("\n");


  httpcall.header = "Content-Type: application/json,User-Agent: ArduinoWiFi/1.1,Accept: */*";
  httpcall.method = "GET";

  httpcall.payload = "{\"name\" : 1}";
  httpcall.protocol = "https";
  httpcall.status = "";

  httpcall.uri = "/";
  httpcall.url = "www.google.com";
  httpcall.url_port = 443;
  httpcall.delimiter = ",";
  httpcall.host = "Host: www.google.com";
  makeHttpCall(&httpcall);
  Serial.print(httpcall.response_status);
  Serial.println("\n");
  Serial.print(httpcall.raw_response);
}

void loop() {
  // put your main code here, to run repeatedly:
}
