# Weight Sensor Application

Using the HX711 sensor board to detect weight using the RPi.

This uses the WiringPi library.

The app will also post the data to http://localhost:3000/weightsensor. Ensure that the `server.js` file in the main directory is running as well.

Helper files:

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

After exporting the pin, you should see a new folder in the `/sys/class/gpio' folder. You can check to see that these pins are set correctly as inputs and outputs by editing the `direction` folder within in each pin's folder (ex. `/sys/class/gpio/gpio23/direction). Input pins should have a single line that says 'in', and output pins should say 'out'.

## References

+ [wiringPi](http://andyseasysite.com/?page_id=145)
+ [RPi Pinout](http://docs.biicode.com/raspberrypi/rpi-howto.html#rpigpio)
