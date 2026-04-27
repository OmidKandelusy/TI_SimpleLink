// including the required header files
#include "gpio_interface.h"

// ====================================================================================
// gpio interface APIs

void gpio_init(button_cb_t *button_one_cb, button_cb_t *button_two_cb){

    if (!button_one_cb || !button_one_cb) return -1;

    GPIO_init();
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_LED_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, button_one_cb);
    GPIO_setCallback(CONFIG_GPIO_BUTTON_1, button_two_cb);
}


void red_led_on(void){
    GPIO_write(CONFIG_GPIO_LED_0, 1);
}

void red_led_off(void){
    GPIO_write(CONFIG_GPIO_LED_0, 0);
}

void red_led_toggle(void){
    GPIO_toggle(CONFIG_GPIO_LED_0);
}

void green_led_on(void){
    GPIO_write(CONFIG_GPIO_LED_0, 1);
}

void green_led_off(void){
    GPIO_write(CONFIG_GPIO_LED_0, 0);
}

void green_led_toggle(void){
    GPIO_toggle(CONFIG_GPIO_LED_0);
}