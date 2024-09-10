/*
 * 
 */

#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXP_PID         "BxzJTQqIqfwsfz"
#define EXP_UUID        "rn01df36446Ca010"
#define EXP_SECRET      "eedecb2c8e444c7fba88719030059596"
#define EXP_MAC         "444AD60B3B66"


typedef struct {
    char uuid[17]; //16+1
    char secret[33]; //32+1
    char mac[13]; //12+1
} TS_LICENSE;

typedef struct {
    char pid[16]; //14+1
    char version;
    //TS_LICENSE license; //pointer??
    char ssid[64];
    char password[64];
    uint8_t binding; //none,BLE,WiFi,LAN
    char mqtt_host[64]; //
    uint32_t mqtt_port;

} TS_DEVICE_INFO;

typedef enum {
    PT_QUEUE_DATA_TYPE_WIFI_STATUS,
    PT_QUEUE_DATA_TYPE_WIFI_GOT_IP,
    PT_QUEUE_DATA_TYPE_BT_RX,
    PT_QUEUE_DATA_TYPE_BT_TX,
    PT_QUEUE_DATA_TYPE_BT_STATUS,
    PT_QUEUE_DATA_TYPE_UDP_RX,
    PT_QUEUE_DATA_TYPE_UART_RX,
    PT_QUEUE_DATA_TYPE_MQTT_STATUS,
    PT_QUEUE_DATA_TYPE_MQTT_RX
} TE_PT_QUEUE_DATA_TYPE;

typedef struct {
    TE_PT_QUEUE_DATA_TYPE type;
    uint16_t len;
    void *data;
} TS_PT_QUEUE_DATA;


_Bool app_queue_push(TS_PT_QUEUE_DATA * q_data);

//notes protco custom
// MTU 200
/***
 * 0x1800 primary Generic Attribute
 *  0x2A05 Service Change [Indicate]
 *  Descriptor 
 *  0x2902 CCC
 *  Client Supported feature
 *  0x2B29 [Read/Write]
 *  Database Hash
 *  0x2B2A [Read]
 *  Server Supported Feature
 *  0x2B3A [Read]
 * 
 * 0x1910 Primary service(Unknown service)
 *  Unknown Charastics
 *  0x2B11 [Write]
 *  Unknown Charastic
 *  0x2B10 [Notify]
 *  0x2902 CCC
 */

#endif //#ifndef __MAIN_H_