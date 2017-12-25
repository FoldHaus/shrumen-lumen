#include <Adafruit_NeoPixel.h>

#include "MotorController.h"

// Pin Definitions
const int DIRECTION_DIGIAL_PIN = 12;
const int SPEED_PWM_PIN = 23;
const int PAD_PIN = 2;
const int NEOPIXEL_DATA_PIN = 3;

//Config Constants
const bool MOTOR_CONTROLLER_DEBUG_MODE = true;
const int LED_STRIP_LENGTH = 16;

// Animation Timings
const unsigned long extensionTime = 15000;
const unsigned long retractionTime = 15000;
const unsigned long freezeTime = 30000;
const unsigned long refreshTime = 30000;

// State Variables
int padState = LOW;
int ledSequence = 0;
int rainbowCount = 0;
bool inProgress = false;
unsigned long timer = 0;
unsigned long sequenceProgressAcc = 0;

// Class Instantiations
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_STRIP_LENGTH, NEOPIXEL_DATA_PIN);
MotorController motorController(DIRECTION_DIGIAL_PIN, SPEED_PWM_PIN, MOTOR_CONTROLLER_DEBUG_MODE);

void setup() {
  pinMode(PAD_PIN, INPUT);
  analogWrite(SPEED_PWM_PIN, 0);

  // Setup NeoPixel Strip & initialize all pixels to 'off'
  strip.begin();
  strip.show();
}

void loop() {
  padState = digitalRead(PAD_PIN);

  if (padState == HIGH || inProgress) {
    if (!inProgress) {
      timer = millis();
    }
    
    animate();
  }
  else {
    motorController.freeze();
    timer = 0;
  }

  // Delay to regulate the LED animations
  delay(20);   
}

void animate() {
  inProgress = true;
  unsigned long delayTime = millis() - timer;
  Serial.println(delayTime);

  // Extension Phase 
  if (delayTime <= extensionTime) {
    motorController.extend();
    ledSequence = 1;
    sequenceProgressAcc = extensionTime;
    Serial.println("Extension Phase");
    Serial.println("Sequence Acc");
    Serial.println(sequenceProgressAcc);
  } 
  // Freeze Phase   
  else if (delayTime > sequenceProgressAcc && delayTime <= freezeTime + sequenceProgressAcc) {
    motorController.freeze();
    ledSequence = 0;
    sequenceProgressAcc = freezeTime + extensionTime;
    Serial.println("Freeze Phase");
    Serial.println("Sequence Acc");
    Serial.println(sequenceProgressAcc);
  }
  // Retraction Phase   
  else if (delayTime > sequenceProgressAcc && delayTime < retractionTime + sequenceProgressAcc) {
    motorController.retract();
    ledSequence = 2;
    sequenceProgressAcc = retractionTime + freezeTime + extensionTime;
    Serial.println("Retraction Phase");
    Serial.println("Sequence Acc");
    Serial.println(sequenceProgressAcc);
  } 
  // Refresh Phase 
  else if (delayTime > sequenceProgressAcc && delayTime <= sequenceProgressAcc + refreshTime) {
    motorController.freeze();
    ledSequence = 0;
    sequenceProgressAcc = refreshTime + retractionTime + freezeTime + extensionTime;
    Serial.println("Refresh Phase");
    Serial.println("Sequence Acc");
    Serial.println(sequenceProgressAcc);
  } 
  // End of Sequence 
  else {
    // Reset all the state variables
    inProgress = false;
    sequenceProgressAcc = 0;
    
    Serial.println("Animation End");
  }

  lightStrip(ledSequence);
}

void lightStrip(int lightSequence) {
  // 0 - Wipe to Dark 
  // 1 - Theater Chase
  // 2 - Rainbow

  switch (lightSequence) {
    case 0:
      colorWipe(0);
      break;
    case 1:
      rainbowCycle();
      break;
    case 2:
      colorWipe(27);
      break;
    default:
      rainbowCycle();
      break;
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle() {
  uint16_t i;
  rainbowCount += 1;

  for(i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + rainbowCount) & 255));
  }

  strip.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
