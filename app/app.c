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

// ====================================================================================
// global variables, constants and other definitions


static t_work_t app_tx_dispatcher_work;

#define TASK_SLEEP_MS 5000

static volatile unit8_t application_event;


/** tx work event flags */
#define NO_EVENT 0xFF
#define LEFT_BUTTON_PRESSED 0xA0
#define RIGHT_BUTTON_PRESSED 0xA1
#define SHELL_MESSAGE_TO_SEND 0xA2
// ====================================================================================
// app helper functions

void event_got_served(void){
    // setting the application event flag:
    application_event = NO_EVENT;
}

// ====================================================================================
// callbacks and ISR routines

void left_button_cb(uint8_t data){
    // setting the application event flag:
    application_event = LEFT_BUTTON_PRESSED;
}

void right_button_cb(uint8_t data){
    // setting the application event flag:
    application_event = RIGHT_BUTTON_PRESSED;
}

void uart_read_handler(uint8_t *data, uint16_t data_len){
    // setting the application event flag:
    application_event = SHELL_MESSAGE_TO_SEND;
}


void app_tx_work_clock_cb(UArg arg){
    Semaphore_post(app_tx_dispatcher_work.ti_semaphore_handle);
}
void app_tx_work_handler(UArg arg0, UArg arg1){
    int err = 0;
    while (1){
        Semaphore_pend(app_tx_dispatcher_work.ti_semaphore_handle);

        switch (application_event){
            case LEFT_BUTTON_PRESSED:
                // left button subroutine handler:
                err = left_button_app_routine();
                break;
            
            case RIGHT_BUTTON_PRESSED:
                err = right_button_app_routine();
                break;

            case SHELL_MESSAGE_TO_SEND:
                break;
                err = send_msg_app_routine();

            default:
                break;
        }


        // task sleep to avoid hogging up the cpu by this thread:
        Task_sleep(TASK_SLEEP_MS);
    }
}
// ====================================================================================
// main application routine

void *mainThread(void *arg0)
{
    int ret = 0;

    // initializing the subsystems
    ret = gpio_init(left_button_cb, right_button_cb);
    if (ret < 0) while (1);

    ret = uart_init(uart_read_handler);
    if (ret < 0) while (1);

    ret = radio_init();
    if (ret < 0) while (1);

    // application tx work:
    app_tx_dispatcher_work.work_handler = app_tx_work_handler;
    app_tx_dispatcher_work.clock_handler = app_tx_work_clock_cb;
    ret = work_init(&app_tx_dispatcher_work);
    if (ret <0 ) while (1);
    

    return 0;
}
