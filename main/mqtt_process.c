
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
//#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

#include "mqtt_process.h"

#define MQTT_TASK_TAG "MQTT_TASK"

static esp_mqtt_client_handle_t mqtt_client;

static void app_mqtt_subscribe_topics(void);

static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(MQTT_TASK_TAG, "Last error %s: 0x%x", message, error_code);
    }
}

/*
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(MQTT_TASK_TAG, "Event dispatched from event loop base=%s, event_id=%" PRIi32 "", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(MQTT_TASK_TAG, "MQTT_EVENT_CONNECTED");

        //TODO: subscribe to all topics
        app_mqtt_subscribe_topics();

        //msg_id = esp_mqtt_client_publish(client, "/topic/qos1", "data_3", 0, 1, 0);
        //ESP_LOGI(MQTT_TASK_TAG, "sent publish successful, msg_id=%d", msg_id);

        //msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
        //ESP_LOGI(MQTT_TASK_TAG, "sent subscribe successful, msg_id=%d", msg_id);

        //msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
        //ESP_LOGI(MQTT_TASK_TAG, "sent subscribe successful, msg_id=%d", msg_id);

        //msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
        //ESP_LOGI(MQTT_TASK_TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(MQTT_TASK_TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(MQTT_TASK_TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        //msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
        //ESP_LOGI(MQTT_TASK_TAG, "sent publish successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(MQTT_TASK_TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(MQTT_TASK_TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(MQTT_TASK_TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        //TODO: check and filter topic
        // then dispatch for further processing 
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(MQTT_TASK_TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(MQTT_TASK_TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

        }
        break;
    default:
        ESP_LOGI(MQTT_TASK_TAG, "Other event id:%d", event->event_id);
        break;
    }
}

static void app_mqtt_subscribe_topics(void){
    char topic[256] = {0,};
    uint16_t len;
    int msg_id;

    uint8_t i;

    for(i = 0; i <  0; i++){
        //
        len = snprintf(topic,254,"rlink/v2/%s/%s/%s","diviceid","","");

        if(len != 0){
            msg_id = esp_mqtt_client_subscribe(mqtt_client, topic, 0);
        }
    }

}

void pt_mqtt_init(void)
{
    ESP_LOGI(MQTT_TASK_TAG, "[mqtt] Startup..");
    
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    //ESP_ERROR_CHECK(example_connect()); //TODO:

    esp_mqtt_client_config_t mqtt_cfg = {
        
        .broker.address.uri = "test.mosquitto.org",
        .broker.address.port =1883,

        .credentials.username = "",
        .credentials.client_id = "",
        .credentials.set_null_client_id = false,
        .credentials.authentication.password = ""

    };

    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(mqtt_client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(mqtt_client);
}

