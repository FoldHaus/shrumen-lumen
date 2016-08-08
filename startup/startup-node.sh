#!/bin/sh

echo "Starting Node server..."
echo `which node`
sudo /usr/bin/node /home/pi/Desktop/pi-server/server.js &
sudo bash /home/pi/Desktop/pi-server/WeightSensor/sensor2.sh

