#!/bin/bash

echo "Add hard links to the systemd commands"
chmod +x /home/pi/Desktop/pi-server/startup/startup-node.sh
chmod +x /home/pi/Desktop/pi-server/startup/startup-pixelpusher.sh
chmod +x /home/pi/Desktop/pi-server/startup/startup-weightsensor.sh
chmod +x /home/pi/Desktop/pi-server/startup/startup-linearactuator.sh
chmod +x /home/pi/Desktop/pi-server/startup/startup-padlights.sh

echo "Add hard links to the systemd commands"
sudo ln /home/pi/Desktop/pi-server/startup/startup-node.service /lib/systemd/system/startup-node.service
sudo ln /home/pi/Desktop/pi-server/startup/startup-pixelpusher.service /lib/systemd/system/startup-pixelpusher.service
sudo ln /home/pi/Desktop/pi-server/startup/startup-weightsensor.service /lib/systemd/system/startup-weightsensor.service
sudo ln /home/pi/Desktop/pi-server/startup/startup-linearactuator.service /lib/systemd/system/startup-linearactuator.service
sudo ln /home/pi/Desktop/pi-server/startup/startup-padlights.service /lib/systemd/system/startup-padlights.service

echo "Enable systemd commands"
sudo systemctl reenable /home/pi/Desktop/pi-server/startup/startup-node.service
sudo systemctl reenable /home/pi/Desktop/pi-server/startup/startup-pixelpusher.service
sudo systemctl reenable /home/pi/Desktop/pi-server/startup/startup-weightsensor.service
sudo systemctl reenable /home/pi/Desktop/pi-server/startup/startup-linearactuator.service
sudo systemctl reenable /home/pi/Desktop/pi-server/startup/startup-padlights.service
