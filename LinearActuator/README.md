# Linear Actuator Application

Using the Cytron MD30C motor controller to drive the 16A linear actuator using the RPi.

This uses the WiringPi library.

The app will also post the data to http://localhost:3000/linearactuator. Ensure that the `server.js` file in the main directory is running as well.

Helper files: [TO BE CHANGED]

+ `sensor1.sh` - Runs application for sensor 1
        + VCC - pin 4
        + DAT - pin 10 (GPIO 15)
        + CLK - pin 12 (GPIO 18)
        + GND - pin 14

+ `sensor2.sh` - Runs application for sensor 2
        + VCC - pin 2
        + DAT - pin 16 (GPIO 23)
        + CLK - pin 18 (GPIO 24)
        + GND - pin 20

** NOTE: Pins must be exported to work **

To export a pin, for example GPIO 23:
`echo 23 > /sys/class/gpio/export`

After exporting the pin, you should see a new folder in the `/sys/class/gpio' folder. You can check to see that these pins are set correctly as inputs and outputs by editing the `direction` folder within in each pin's folder (ex. `/sys$

## References

+ [wiringPi](http://andyseasysite.com/?page_id=145)
+ [RPi Pinout](https://pinout.xyz/)

