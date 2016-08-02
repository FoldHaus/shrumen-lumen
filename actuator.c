#include <wiringPi.h>


int main(void) {
	
	int dataPin = 7;
	wiringPiSetup();
	pinMode(dataPin, OUTPUT);

	digitalWrite(dataPin, HIGH);
	delay(1);
	digitalWrite(dataPin, LOW);

	delay(3000);

	digitalWrite(dataPin, HIGH);
	delay(2);
	digitalWrite(dataPin, LOW);
	delay(3000);

}

