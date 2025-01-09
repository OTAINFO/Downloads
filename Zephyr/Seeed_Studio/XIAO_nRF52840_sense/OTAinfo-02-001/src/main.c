
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>
#include <zephyr/sys/util.h>
#include <string.h>
#include <hal_02_seeed_studio_xiao_nrf52840_sense.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>

int main(void)
{
	otainfo_initialize();
    //* Initialize the BT subsystem */
	int err = 0;
    err = bt_enable(NULL);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }
    printk("Bluetooth initialized\n");
    //* Start advertising */
    bt_le_adv_start(BT_LE_ADV_CONN, NULL, 0, NULL, 0);

}