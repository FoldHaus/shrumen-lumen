#!/bin/sh


#Automatically Start Weight Sensor Script
echo "Start the weight sensor script..."

#Export Pins
echo 15 > /sys/class/gpio/export
echo 18 > /sys/class/gpio/export
echo 23 > /sys/class/gpio/export
echo 24 > /sys/class/gpio/export

sudo ./sensor1.sh
sudo ./sensor2.sh

exit 0

