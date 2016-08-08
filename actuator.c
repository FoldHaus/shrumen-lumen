#include <stdio.h>
#include <wiringPi.h>

int dataPin = 25;

void move(int repeat, int speed){
	int i;
	for(i = 0; i < repeat; i ++){
		printf("%d / %d moving at speed %d\n", i, repeat, speed);
		softPwmWrite(dataPin, speed);
		delay(1000);
	}
	softPwmWrite(dataPin, 0);
	delay(1000);
}

void digiForward(dataPin) {
	digitalWrite(dataPin, HIGH);
	delay(2)
	digitalWrite(dataPin, LOW);
	delay(10);

}

void digiStop(dataPin) {
	
	digitalWrite(dataPin, HIGH);
	delay(1.5)
	digitalWrite(dataPin, LOW);
	delay(10);

}

void digiBack(dataPin) {
	digitalWrite(dataPin, HIGH);
	delay(1)
	digitalWrite(dataPin, LOW);
	delay(10);

}



int main(void) {
	wiringPiSetup();
	pinMode(dataPin, OUTPUT);
	//~ digitalWrite(dataPin, LOW);
	
	for(i = 0; i < 5; i++){
		
	}
	
	//~ softPwmCreate(dataPin, 0, 200);
	//~ delay(5000);
	
	//~ int i;
	//~ for(i = 0; i < 5; i++){
		//~ 
		//~ 
		//~ move(1, 10);
		//~ move(1, 15);
		//~ move(1, 10);
		//~ move(1, 15);
		//~ move(20, 10);
		//~ 
		//~ move(25, 15);
		//~ 
		//~ move(1, 15);
		//~ move(1, 20);
		//~ move(1, 15);
		//~ move(1, 20);
		//~ move(1, 15);
		//~ move(20, 20);
		//~ 
		//~ move(25, 15);
	//~ }
	
	return 0;
}

