#include <wiringPi.h>
#include <stdio.h>
#include <sched.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"


#define GET_URL "http://localhost:3000/linearactuator"
#define DIRECTION_PIN 6
#define PWM_PIN 12
#define MIN_DELAY_TIME 5000

//~ int directionPin = 6;
//~ int pwmPin = 12;

int state = 1;

void setup_gpio()
{
  pinMode(DIRECTION_PIN, OUTPUT);
  pinMode(PWM_PIN, PWM_OUTPUT);
}

int getState(int data){
	char cmd[200];
	sprintf(cmd,
		"curl -X GET %s -H \"Content-Type: application/json\" ",
		GET_URL);
	//~ int state = cJSON_GetObjectItem(cmd,"current state")->valueint;
	printf("cmd: %s\n", cmd);
	system(cmd);
}

void retract() {
	stop();
	printf("Waiting for minimum delay time of ");
	printf("%d\n", MIN_DELAY_TIME);
	delay(MIN_DELAY_TIME);
	printf("Retracting...\n");
	digitalWrite(DIRECTION_PIN, HIGH);
	pwmWrite(PWM_PIN, 1024);
}

void extend() {
	printf("Extending...\n");
	digitalWrite(DIRECTION_PIN, LOW);
	pwmWrite(PWM_PIN, 1024);
}

void stop() {
	printf("Stopping...\n");
	pwmWrite(PWM_PIN, 0);
}

int main(int argc, char **argv)
{
	//Setup WiringPi w/ GPIO pins
	if(wiringPiSetupGpio() == -1)
		exit(1);
	
	// Set the pins to the correct output types.
	setup_gpio();
	
	while(1) {
		if(state == 1) {
			extend();
		}
		else if(state == 0) {
			stop();
		}
		else if (state == -1){
			retract()
		}			
	}
}
