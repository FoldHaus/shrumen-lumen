#!/bin/sh

#Automatically Start Weight Sensor Script
echo "Start the weight sensor script..."

#Export Pins
echo 6 > /sys/class/gpio/export
echo 12 > /sys/class/gpio/export

#Starts the LA script
sudo /home/pi/Desktop/pi-server/LinearActuator/LinearActuator



