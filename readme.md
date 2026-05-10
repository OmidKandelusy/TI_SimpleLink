# Description
This repository illustrates how the simplelink sdk by Texas Instruments can be used to implement embedded projects. In specific, this project implements a shell over subGHz wireless communication where two devices can send commands to each other over the wireless link. The user can configure the wireless connection for a specific frequency band. This project clearly shows how to use : 

- TI RTOS threads and features  for real time applications.
- main peripherals like UART, Radio Core, GPIO, and timers.
- ecplise build environment in the simplelink sdk.

## project configuration
The SimpleLink SDK is using a configuration tooling called [SysConfig](docs/getting_started_with_sysconfig.pdf) to configure the projects in the compile time. In the following, the configurations used for this project are explained.

**GPIO:** in this project we use the buttons and leds on the launchpads, so we should configure them properly in the compile time. This includes the token used for identifications of the pins and type of the pins. Particularly, opening the sysconfig GUI in the CCS as the screenshot [here](/docs/images/GPIO_Sysconfig.png), we add four GPIO items for two buttons and two LEDs on the launchpad board. We set the mode to output for the LED and input for the buttons. Also, we enable the interrupt for the button pins.

**UART:** another peripheral that utilize in this project is the UART. To properly initiate the uart driver we need to make some compile time settings like pin multiplexing, blocking behavior, and a token representing the peripheral. Particulary, similar to the gpio case, we use the the sysconfig GUI to add an UART instance with our desirable configurations as the screenshot [here](/docs/images/UART_Sysconfig.png).

**Radio:** in order to set up and use the radio core in a way that we are interested, we should configure several parameters via the sysconfig and during the compile time including, data rate, bandwidth, frequency ranges, modulation schemes, transmit power. For this project, we are interested in creating a custom and proprietary the subGHz connectivity and therefore we add custom radio object to the sysconfig as the screenshot [here](/docs/images/radio_sysconfig.png).

Note: since this example is intended for the use in the EU region, the default frequency range is set to 868MHz. Furthermore, to configure the radio core properly, there are more dependencies to set up in the sysconfig as well. In details, 
- code export: we should set this custom
- RF design: add one RF design and set Use Hardware to the SKY antenna selector

## setup and build
In order to build the projects in this repository, it is needed to add the `ANCHOR` path variable to the code composer studio. To do so, go to project properties, then variables from the general tab. There add a new path variable where the name must be `ANCHOR` and the value must be the path to the repository on the host machine. This variable is used to properly pull in different source and header files into the build system.

## Running the app
The target platform for this repository is cc1352p7-1. There are two great boards that can be used to test the firmware. The first one is the launchpad development board by Texas Instruments and the second one is the Beagle Connect freedom. However, to work with the beagle board there are a few important things that needed to be paid attention to because the beagle board does not expose JTAG or SWD pins for debugger and relies on the rom bootloader.So, before flashing anything , it is critical to enable the bootloader on the firmware as:

    1. Go to sysconfig, then device configuration tab
    2. check the `Enable Bootloader`
    3. check the `Enable Bootloader Backdoor`
    4. set the backdoor gpio pin to the boards reboot pin which is `DIO15`
    5. set the trigger level of bootloader backdoor to `Active Low`

In order to flash, first install the python flasher tool as 
- pip install cc1352p7-flasher

Next, use the flasher script as
- cc1352-flasher -p /dev/ttyUSBx -e -w -v your_firmware.hex

# Release Note:
The current version of the application, that is being built incrementally, would be operating in an override mode without any task queue. Once the first version of the app is completed as tagged, the next version of the application would evolve into a priority queue based for application events.