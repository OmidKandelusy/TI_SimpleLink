// including the required header files
#include "gpio_interface.h"

// ====================================================================================
// gpio interface APIs

int gpio_init(button_cb_t button_one_cb, button_cb_t button_two_cb){

    if (!button_one_cb || !button_one_cb) return -1;

    GPIO_init();
    GPIO_setConfig(CONFIG_RED_LED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GREEN_LED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_LEFT_BUTTON, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    GPIO_setConfig(CONFIG_RIGHT_BUTTON, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    GPIO_setCallback(CONFIG_LEFT_BUTTON, button_one_cb);
    GPIO_setCallback(CONFIG_RIGHT_BUTTON, button_two_cb);

    return 0;
}


void red_led_on(void){
    GPIO_write(CONFIG_RED_LED, 1);
}

void red_led_off(void){
    GPIO_write(CONFIG_RED_LED, 0);
}

void red_led_toggle(void){
    GPIO_toggle(CONFIG_RED_LED);
}

void green_led_on(void){
    GPIO_write(CONFIG_GREEN_LED, 1);
}

void green_led_off(void){
    GPIO_write(CONFIG_GREEN_LED, 0);
}

void green_led_toggle(void){
    GPIO_toggle(CONFIG_GREEN_LED);
}