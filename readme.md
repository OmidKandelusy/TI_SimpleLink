# Description
This repository illustrates how the simplelink sdk by Texas Instruments can be used to implement embedded projects. In specific, this project implements a shell over subGHz wireless communication where two devices can send commands to each other over the wireless link. The user can configure the wireless connection for a specific frequency band. This project clearly shows how to use : 

- TI RTOS threads and features  for real time applications.
- main peripherals like UART, Radio Core, GPIO, and timers.
- ecplise build environment in the simplelink sdk.

## project configuration
The SimpleLink SDK is using a configuration tooling called [SysConfig](docs/getting_started_with_sysconfig.pdf) to configure the projects in the compile time. In the following, the configurations used for this project are explained.

**GPIO:** in this project we use the buttons and leds on the launchpads, so we should configure them properly in the compile time. This includes the tocken used for identifications of the pins and type of the pins. Particularly, as shown below, we add four GPIO items for two buttons and two LEDs on the launchpad board. We set the mode to output for the LED and input for the buttons. Also, we enable the interrupt for the button pins:

![gpio_sysconfig_image](/docs/images/GPIO_Sysconfig.png)

**UART:** another peripheral that utilize in this project is the UART. To properly initiate the uart driver we need to make some compile time settings like baudrates, blocking behaviour, and a token representing the peripheral.

**Radio:** in order to set up and use the radio core in a way that we are interested, we should configure several parameters via the sysconfig and during the compile time including, data rate, bandwidth, frequency ranges, modulation schemes, transmit power.


This is a work in progress and this readme file will be updated soon.

## setup and build
