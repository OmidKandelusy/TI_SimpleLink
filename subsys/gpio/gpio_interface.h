#ifndef GPIO_INTERFACE_HEADER_G
#define GPIO_INTERFACE_HEADER_G
// ====================================================================================
// including the requried header files

/** standard C header files */
#include <stdint.h>
#include <stdlib.h>

/** gpio driver header files */
#include <ti/drivers/GPIO.h>

// ====================================================================================
// typedefs and macros

/** button callback type */
typedef void (*button_cb_t)(uint8_t state);


// ====================================================================================
// exposed APIs

/** 
 * @brief registers button callbacks from the application
 * 
 * @param [in] button_one_cb function handler to register for button 1
 * @param [in] button_two_cb function handler to register for button 2
 */
void gpio_init(button_cb_t *button_one_cb, button_cb_t *button_two_cb);

/**
 * @brief turns on the green led on the launchpad
 */
void green_led_on(void);

/**
 * @brief turns off the green led on the launchpad
 */
void green_led_off(void);

/**
 * @brief toggles the green led on the launchpad
 */
void green_led_toggle(void);

/**
 * @brief turns on the red led on the launchpad
 */
void red_led_on(void);

/**
 * @brief turns off the red led on the launchpad
 */
void red_led_off(void);

/**
 * @brief toggles the red led on the launchpad
 */
void red_led_toggle(void);

#endif