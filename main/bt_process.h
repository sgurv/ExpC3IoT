
#ifndef __BT_PROCESS_H_
#define __BT_PROCESS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void bt_process_task(void *arg);

#endif
