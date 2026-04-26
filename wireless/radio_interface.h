#ifndef RADIO_INTERFACE_H_GUARD
#define RADIO_INTERFACE_H_GUARD
// ===================================================================================
// including the required headers


/** standard C header files */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** TI readio configuration and driver header files */
#include "RFQueue.h"
#include <ti_radio_config.h>
#include <ti/drivers/rf/RF.h>
#include "ti_drivers_config.h"
#include DeviceFamily_constructPath(driverlib/rf_prop_mailbox.h)

// ===================================================================================
// varaible definitions, macros, and constants

/* Packet Rx configuration */
#define DATA_ENTRY_HEADER_SIZE 8
#define MAX_LENGTH             64
#define NUM_DATA_ENTRIES       2
#define NUM_APPENDED_BYTES     2

/** Tx packet configuration*/
#define AIR_PAYLOAD_LENGTH      30


#endif