# Linear Actuator Application

Using the Cytron MD30C motor controller to drive the 16A linear actuator using the RPi.

This uses the WiringPi library, as well as libcurl4 and cJSON to send GET requests and parse the responses.

The app will also post the data to http://localhost:3000/linearactuator. Ensure that the `server.js` file in the main directory is running as well.

##Installation:
To install libcurl4, run the following:

```
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev
```

The cJSON files are included in the repo. 

Make sure to run `make` when changes are made. The Makefile links the cJSON, libcurl, and math libraries automatically.

##Pins Setup:
Linear Actuator:
+ PWM - Physical Pin 31 (GPIO 6)
+ DIR - Physical Pin 32 (GPIO 12)
+ GND - Physical Pin 34

** NOTE: Pins must be exported to work **

To export a pin, for example GPIO 6:
`echo 6 > /sys/class/gpio/export`

After exporting the pin, you should see a new folder in the `/sys/class/gpio' folder. You can check to see that these pins are set correctly as inputs and outputs by editing the `direction` folder within in each pin's folder (ex. `/sys$

## References

+ [wiringPi](http://andyseasysite.com/?page_id=145)
+ [RPi Pinout](https://pinout.xyz/)

