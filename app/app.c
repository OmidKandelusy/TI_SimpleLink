/**
 * @brief main application routine for the shell over subGhz
 * 
 * @note: after the cpu boots up, the first thing that is run is the main() function
 *        where it would spawn out a posix thread called mainThread. This thread will
 *        be triggered one BIOS_start() command is called. This is the principle used
 *        by TI's simplelink sdk to run firmware images on the cc13xx-cc26xx devices.
 * 
 * Author: Omid Kandelusy
 */
// ====================================================================================
// including the required header files

/* standard C header files */
#include <stdint.h>
#include <stddef.h>

/** inlcuding the application subsystem headers */
#include "gpio/gpio_interface.h"
#include "uart/uart_interface.h"


void left_button_cb(uint8_t data){
    //
}

void right_button_cb(uint8_t data){
    //
}

void uart_read_handler(uint8_t *data, uint16_t data_len){
    //
}


void *mainThread(void *arg0)
{
    int ret = 0;

    // initializing the subsystems
    ret = gpio_init(left_button_cb, right_button_cb);
    if (ret < 0) while (1);

    ret = uart_init(uart_read_handler);
    if (ret < 0) while (1);

    return 0;
}
