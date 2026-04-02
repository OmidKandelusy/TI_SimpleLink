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
#include "wireless/radio_interface.h"
#include "work/t_work.h"


void *mainThread(void *arg0)
{
    int ret = 0;

    // initializing the subsystems
    ret = gpio_init();
    if (ret < 0) while (1);

    ret = uart_init();
    if (ret < 0) while (1);

    ret = radio_init();
    if (ret <0) while (1);

    ret = work_init(&heartbit_work);
    if (ret <0 ) while (1);

    ret = work_init(&shell_work);
    if (ret < 0) while (1);

    ret = work_init(&button_work);
    if (ret <0) while (1);

    ret = work_init(&radio_work);
    if (ret < 0) while (1);

    // starting the main subroutines
    work_start(&hearbit_work);
    work_start(&button_work);
    work_start(&shell_work);
    work_start(&radio_work);

}
