#ifndef UART_INTERFACE_H_GUARD
#define UART_INTERFACE_H_GUARD
// ========================================================================================

/** standard C header files */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/** TI's driver and configuration for uart driver */
#include "ti_drivers_config.h"
#include <ti/drivers/UART2.h>
// ========================================================================================
// typedefs, macros and constants

/** baudrate used by the uart peripheral for decoding the pulses on the line */
#define BAUDRATE 115200

/** the size of the buffer that holds the bytes read from the line */
#define READ_BUFF_SIZE 64

/** uart read callback type */
typedef void (*uart_read_cb)(uint8_t *data, uint16_t len);

// ========================================================================================
// APIs

/**
 * @brief initializes the uart interface for the application
 * 
 * @param [in] cb the read callback that application can register 
 * 
 * @return SUCCESS if succeeds; negative error code otherwise.
 */
int uart_init(uart_read_cb cb);

#endif