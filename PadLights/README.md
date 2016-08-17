# PadLights

Uses rpi-ws281x-native nodejs library to control a strand of NeoPixel leds.

## Pin Setup
Pad Lights:
+ DAT: Physical Pin 12 (GPIO 18)
+ GND: Physical Pin 14

## Running Tests
To Run 60 pixel strand:

`sudo node sample.js 60`

Note that node needs to be run with `sudo` for the light sequence to work.
