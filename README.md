# Shrumen Lumen

Shrumen Lumen software.

# Parts

+ [WeightSensor Application](./WeightSensor)


# RPi Setup Steps

## General Configurations

+ Configure Keyboard: `setxkbmap -layout us`

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

