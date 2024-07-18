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

/* Attributes State Machine */
#if (0)
enum
{
    IDX_SVC,
    IDX_CHAR_A,
    IDX_CHAR_VAL_A,
    IDX_CHAR_CFG_A,

    IDX_CHAR_B,
    IDX_CHAR_VAL_B,

    IDX_CHAR_C,
    IDX_CHAR_VAL_C,

    HRS_IDX_NB,
};
#else
enum {

    PT_IDX_SVC,
    PT_IDX_CHAR_W,
    PT_IDX_CHAR_VAL_W,

    PT_IDX_CHAR_N,
    PT_IDX_CHAR_VAL_N,
    PT_IDX_CHAR_CFG_N,

    PT_IDX_NB,
};
#endif

typedef enum {
    PT_QUEUE_TYPE_BT_RX,
    PT_QUEUE_TYPE_BT_TX
} TE_PT_QUEUE_TYPE;

typedef struct {
    TE_PT_QUEUE_TYPE;
    uint16_t len;
    void *data;
} TS_PT_QUEUE;

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