# Shrumen Lumen (Arduino Edition)

#### Pinout
Motor Controller:
```
const int DIRECTION_DIGIAL_PIN = 12;
const int SPEED_PWM_PIN = 23;
```

Weight-Sensing Pad:
```
const int PAD_PIN = 2;
```

LED Strip:
```
const int NEOPIXEL_DATA_PIN = 3;
```
Note that when attaching a strip, update the variable `LED_STRIP_LENGTH` to the correct number of LEDs on the strip.

### Additional Notes
When attaching a new LED strip, update the variable `LED_STRIP_LENGTH` to the correct number of LEDs on the strip.
```
const int LED_STRIP_LENGTH = 60;
```

If you'd like to see Serial Monitor logging of the state of the motor controller during development, you can set the `MOTOR_CONTROLLER_DEBUG_MODE` flag to `true`.
```
const bool MOTOR_CONTROLLER_DEBUG_MODE = true;
```
