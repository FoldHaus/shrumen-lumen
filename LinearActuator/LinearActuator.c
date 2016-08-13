#include <wiringPi.h>
#include <stdio.h>
#include <sched.h>
#include <string.h>
#include <stdlib.h>

#define GET_URL "http://localhost:3000/linearactuator"

int directionPin = 6;
int pwmPin = 12;


void setup_gpio()
{
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, PWM_OUTPUT);
}

int getState(int data){
	char cmd[200];
	sprintf(cmd,
		"curl -X GET %s -H \"Content-Type: application/json\" -d '{ \"sensor\": %d, \"data\": %d }'",
		GET_URL,
		1,
		1);
	printf("cmd: %s\n", cmd);
	system(cmd);
}

void retract() {
	printf("Retracting...\n");
	digitalWrite(directionPin, HIGH);
	pwmWrite(pwmPin, 1024);
}

void extend() {
	printf("Extending...\n");
	digitalWrite(directionPin, LOW);
	pwmWrite(pwmPin, 1024);
}

void stop() {
	printf("Stopping...\n");
	pwmWrite(pwmPin, 0);
}

int main(int argc, char **argv)
{
	if(wiringPiSetupGpio() == -1)
		exit(1);
	
	
	// Set the pins to the correct output types.
	setup_gpio();
	
	extend();
	delay(5000);
	
	stop();
	delay(2000);
	
	retract();
	delay(5000);
}
