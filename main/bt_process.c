#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"

#include "main.h"
#include "bt_process.h"

QueueHandle_t btQueue = NULL;

void bt_process_task(void *arg){

    btQueue = xQueueCreate(5,(sizeof(TS_PT_QUEUE)));

    while(1){

    }
}
