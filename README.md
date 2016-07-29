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

<sup>References: [http://thisdavej.com/beginners-guide-to-installing-node-js-on-a-raspberry-pi/](http://thisdavej.com/beginners-guide-to-installing-node-js-on-a-raspberry-pi/)</sup>

## Running Scripts On Boot Up
In order to run scripts on boot, you must edit the `/etc/rc.local` file. 

At the top of the file (underneath the first comment block), add:
```
exec 2> /home/pi/Desktop/rc.local.log      # send stderr from rc.local to a log file
exec 1>&2                                  # send stdout to the same log file
set -x                                     # tell sh to display commands before execution
```
Adding these commands will tell the Raspberry Pi to put the output and errors that come from the rc.local script into a log file on your Desktop called `rc.local.log`.

Above the `exit 0` that's on the last line of the file, add:
```
# Automatically Run Scripts for Shrumen Lumen
node /home/pi/Desktop/<project_directory>/<node_server_file> &
processing-java --sketch=/home/pi/Desktop/<project-directory>/server_test -- run &
```

After making these changes, double check that you have:
+ Not removed the `exit 0` line at the end of the file.
+ Added ampersands to the end of each line that will run a continuous command that you want to run in the background.

 
