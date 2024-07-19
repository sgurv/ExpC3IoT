
/****************************************************************************
*
* 
****************************************************************************/


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"
#include "main.h"
#include "esp_gatt_common_api.h"
#include "bt_process.h"

#define GATTS_TABLE_TAG "ExpIoT"


void app_main(void)
{


    xTaskCreate(bt_process_task, "BT_Task", 4096, NULL, 6, NULL);
}
