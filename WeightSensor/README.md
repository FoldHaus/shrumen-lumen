# Weight Sensor Application

Using the HX711 sensor board to detect weight using the RPi.

This uses the WiringPi library.

The app will also post the data to http://localhost:3000/weightsensor. Ensure that the `server.js` file in the main directory is running as well.

The `sensor.sh` file exports the necessary pins automatically, and starts the weight sensor program. You can start the program using `sudo bash sensor.sh`, though this script should start automatically (see the [startup files](./startup). 

##Pin Setup
Weight Sensor:
+ VCC - Physical Pin 2
+ DAT - Physical Pin 16 (GPIO 23)
+ CLK - Physical Pin 18 (GPIO 24)
+ GND - Physical Pin 20

** NOTE: Pins must be exported to work **

To export a pin, for example GPIO 23:
`echo 23 > /sys/class/gpio/export`

After exporting the pin, you should see a new folder in the `/sys/class/gpio' folder. You can check to see that these pins are set correctly as inputs and outputs by editing the `direction` folder within in each pin's folder (ex. `/sys/class/gpio/gpio23/direction). Input pins should have a single line that says 'in', and output pins should say 'out'.

## References

+ [wiringPi](http://andyseasysite.com/?page_id=145)
+ [RPi Pinout](https://pinout.xyz/)
