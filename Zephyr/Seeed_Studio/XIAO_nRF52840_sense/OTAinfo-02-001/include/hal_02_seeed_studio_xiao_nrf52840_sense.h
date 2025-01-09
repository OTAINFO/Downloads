//
/// Copyright (c) 2024 OTAinfo, Inc. USA, All rights are reserved.
//

#include <zephyr/zephyr.h>
#include <zephyr/net/socket.h>
#include <zephyr/net/net_ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zephyr/bluetooth/uuid.h>


#ifndef hal_02_seeed_studio_xiao_nrf52840_sense_H
#define hal_02_seeed_studio_xiao_nrf52840_sense_H

typedef struct {
  char *name;
} BLEConnData;

typedef struct {
  double x_val;
  double y_val;
  double z_val;
}AcclerometerData;

typedef struct{
  double Gx;
  double Gy;
  double Gz;
  int sample_rate_hz;
} GyroscopeData;

void otainfo_initialize();

#endif
