
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
#include "mqtt_process.h"

#define GATTS_TABLE_TAG "ExpIoT"

QueueHandle_t xApp_queue_handle;

static _Bool app_queue_init(void){
    xApp_queue_handle = xQueueCreate(10,(sizeof(TS_PT_QUEUE_DATA)));
    if(xApp_queue_handle == NULL){
        return false;
    }
    return true;
}

static _Bool app_queue_pop(TS_PT_QUEUE_DATA * q_data){

    if(xApp_queue_handle == NULL){
        return false;    
    }

    if(xQueueReceive(xApp_queue_handle, q_data, (TickType_t)0) != pdPASS){
        return false; //error of no data
    }

    return true; // success
}

_Bool app_queue_push(TS_PT_QUEUE_DATA * q_data){
    
    if(xApp_queue_handle == NULL){
        return false;    
    }

    if(xQueueSend( xApp_queue_handle,(void*)q_data ,( TickType_t ) 0 ) != pdPASS )
    {
        return false;
    }

    return true;
}

void app_main(void)
{

    TS_PT_QUEUE_DATA main_queue_data;

    xTaskCreate(bt_process_task, "BT_Task", 4096, NULL, 6, NULL);


    if(app_queue_init() == false){
        // queue init failed

        // wait and restart
    }

    // let's use app_main() as main task
    while(1){
        // wait for mesage
        if(app_queue_pop(&main_queue_data) != true){
            vPortYield();
            continue;
        }

        switch(main_queue_data.type){
            case PT_QUEUE_DATA_TYPE_WIFI_STATUS:
            break;
            case PT_QUEUE_DATA_TYPE_WIFI_GOT_IP:
                //MQTT start
                pt_mqtt_init();
                //NTP Sync
            
            break;
            case PT_QUEUE_DATA_TYPE_BT_RX:
                //
            break;
            case PT_QUEUE_DATA_TYPE_BT_TX:
            break;
            case PT_QUEUE_DATA_TYPE_BT_STATUS:
            break;
            case PT_QUEUE_DATA_TYPE_UDP_RX:
            break;
            case PT_QUEUE_DATA_TYPE_UART_RX:
            break;
            case PT_QUEUE_DATA_TYPE_MQTT_STATUS:
            break;
            case PT_QUEUE_DATA_TYPE_MQTT_RX:
            break;    
            default:
            break;
        }

    }
}
