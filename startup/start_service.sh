#!/bin/bash

echo "Add hard links to the systemd commands"
chmod +x startup-node.sh
chmod +x startup-pixelpusher.sh
chmod +x startup-weightsensor.sh
chmod +x startup-linearactuator.sh
chmod +x startup-padlights.sh

echo "Add hard links to the systemd commands"
sudo ln startup-node.service /lib/systemd/system/startup-node.service
sudo ln startup-pixelpusher.service /lib/systemd/system/startup-pixelpusher.service
sudo ln startup-weightsensor.service /lib/systemd/system/startup-weightsensor.service
sudo ln startup-linearactuator.service /lib/systemd/system/startup-linearactuator.service
sudo ln startup-padlights.service /lib/systemd/system/startup-padlights.service

echo "Enable systemd commands"
sudo systemctl reenable startup-node.service
sudo systemctl reenable startup-pixelpusher.service
sudo systemctl reenable startup-weightsensor.service
sudo systemctl reenable startup-linearactuator.service
sudo systemctl reenable startup-padlights.service
