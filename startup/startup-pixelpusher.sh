#!/bin/sh

# exec 2> /home/pi/Desktop/rc.local.log  #send stderr from rc.local to a log file
# exec 1>&2                              #send stdout to the same log file
# set -x                                 #tell sh to displace commands before exe$

# Print the IP address
_IP=$(hostname -I) || true
if [ "$_IP" ]; then
  printf "My IP address is %s\n" "$_IP"
fi

echo "I AM:", `whoami`

echo "Starting background Display 2..."
sudo Xvfb :2 -screen 0 1024x768x24 &
export DISPLAY=":2"


#Automatically Run Scripts for Shrumen Lumen
echo "Start the processing script..."
processing-java --sketch=/home/pi/Desktop/pi-server/server_test --run
exit 0

