# GG86

![GG86](https://i.imgur.com/SgXOZjt.png?2)

Support Atmega32u4 keyboard.

* Keyboard Maintainer: Gopolar
* Hardware Supported: Atmega32u4

Make example for this keyboard (after setting up your build environment):

    make gopolar/gg86:default 

Flashing example for this keyboard:

    make gopolar/gg86:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
* **Physical reset button**: Short press the button on the back of the PCB to enter the Bootloader and flash the firmware
* **Keycode in layout**: Press the key mapped to RESET if it is available
