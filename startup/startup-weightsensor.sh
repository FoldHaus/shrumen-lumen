#!/bin/sh


#Automatically Start Weight Sensor Script
echo "Start the weight sensor script..."

#Export Pins
echo 15 > /sys/class/gpio/export
echo 18 > /sys/class/gpio/export
echo 23 > /sys/class/gpio/export
echo 24 > /sys/class/gpio/export
bash /home/pi/Desktop/pi-server/WeightSensor/sensor1.sh
bash /home/pi/Desktop/pi-server/WeightSensor/sensor2.sh




