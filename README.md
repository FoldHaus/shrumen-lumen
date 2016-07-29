# Shrumen Lumen

Shrumen Lumen software.

# Parts

+ [WeightSensor Application](./WeightSensor)


# RPi Setup Steps

## General Configurations
#### One-time Configuration:
+ Configure Keyboard: `setxkbmap -layout us`

#### Permanent Configuration:
+ Use `sudo raspi-config` to open the Raspberry Pi configuration too.
+ Select _Internationalisation Options_ from the list.
+ Select _Change Keyboard Layout_. It may take a few seconds for the next window to open.
+ Select the _Generic 101-key PC_.
+ Select _Other_ at the bottom for the _Keyboard layout_ list.
+ Select _English (US)_ from the list.

Respond _No_ to the following prompts.

## Setup RaspberryPi

+ Install: `curl https://processing.org/download/install-arm.sh | sudo sh`
+ Update graphics: `sudo aptitude remove libgles2-mesa`
+ Install 'PixelPusher' Library
+ Install 'HTTP Requests for Processing' Library

<sup>References: [https://github.com/processing/processing/wiki/Raspberry-Pi](https://github.com/processing/processing/wiki/Raspberry-Pi)</sup>

## Setup Node

+ Setup remote: `curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -`
+ Install node: `sudo apt-get install -y nodejs`

<sup>References: [http://thisdavej.com/beginners-guide-to-installing-node-js-on-a-raspberry-pi/](http://thisdavej.com/beginners-guide-to-installing-node-js-on-a-raspberry-pi/)

