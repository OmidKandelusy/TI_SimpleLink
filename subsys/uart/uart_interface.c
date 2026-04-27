#include "uart_interface.h"


// ========================================================================================
// variable definitions

/** uart peripheral driver configuration variables */
static UART2_Handle handle;
static UART2_Params params;
static int read_bytes = 0;
static uint8_t read_buff[READ_BUFF_SIZE]

/** user callback registery for the read events */
static uart_read_cb user_cb = NULL;
// ========================================================================================
// callbacks and helper functions

void uart_callback(UART2_Handle handle, void *buffer, size_t count,
                         void *userArg, int_fast16_t status){
    if (user_cb){
        user_cb(buffer, count);
    }
}

// ========================================================================================
// main functions

int uart_init(uart_read_cb cb){
    if (!cb) return -1;

    UART2_Params_init(&params);
    params.baudRate = BAUDRATE;
    params.writeMode = UART2_Mode_BLOCKING;
    params.readMode = UART2_Mode_CALLBACK;
    params.readCallback = uart_callback;
    params.readReturnMode = UART2_ReadReturnMode_PARTIAL;


    handle = UART2_open(CONFIG_UART_OBJ, &params);
    if (!handle){
        return -1;
    }

    UART2_read(handle, read_buff, READ_BUFF_SIZE, &read_bytes);

    const char init_msg[] = "\n\r uart interface is initialized \n\r";
    UART2_write(handle, init_msg, sizeof(init_msg), NULL);

    return 0;
};