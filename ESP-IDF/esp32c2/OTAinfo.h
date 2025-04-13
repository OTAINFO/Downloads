#ifndef OTAINFO_H
#define OTAINFO_H

  void check_panic();
  bool can_rollback();
  bool ota_partition_check();
  void ota_update_task(void *pvParameter);
  void start_ota(char* url);
  void get_running_partition();

#endif