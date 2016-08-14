#include <wiringPi.h>
#include <stdio.h>
#include <sched.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "cJSON.h"


#define GET_URL "http://localhost:3000/linearactuator"
#define DIRECTION_PIN 6
#define PWM_PIN 12
#define MIN_DELAY_TIME 1000

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}


int state = 0;
void setup_gpio()
{
  pinMode(DIRECTION_PIN, OUTPUT);
  pinMode(PWM_PIN, PWM_OUTPUT);
}

void getState(){
	
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	
	if(curl) {
		struct string s;
		init_string(&s);
		curl_easy_setopt(curl, CURLOPT_URL, GET_URL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		
		/* Check for errors */ 
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		}
		
		cJSON * json = cJSON_Parse(s.ptr);
		state = cJSON_GetObjectItem(json, "state")->valueint;
		cJSON_Delete(json);
		printf("New State: %d\n", state);
		free(s.ptr);
		
		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	
	curl_global_cleanup();
}

void stopActuator() {
	printf("Stopping...\n");
	pwmWrite(PWM_PIN, 0);
}

void retractActuator() {
	stopActuator();
	printf("Waiting for minimum delay time of ");
	printf("%d\n", MIN_DELAY_TIME);
	delay(MIN_DELAY_TIME);
	printf("Retracting...\n");
	digitalWrite(DIRECTION_PIN, HIGH);
	pwmWrite(PWM_PIN, 1024);
	delay(1000);
	stopActuator();
}

void extendActuator() {
	printf("Extending...\n");
	digitalWrite(DIRECTION_PIN, LOW);
	pwmWrite(PWM_PIN, 1024);
}

int main(int argc, char **argv) {
	
	
	printf("At least this works");

	//Setup WiringPi w/ GPIO pins
	if(wiringPiSetupGpio() == -1)
		exit(1);
	//~ 
	//~ // Set the pins to the correct output types.
	setup_gpio();
	
	//~ stopActuator();
	
	while(1) {
		usleep(500 * 1000);
		
		//~ Run CURL GET command
		getState();
		
		printf("%d\n", state);
		if(state == 1) {
			printf("WOULD EXTEND");
			extendActuator();
		}
		else if(state == 0) {
			printf("WOULD STOP");
			retractActuator();
		}
		else if (state == -1){
			printf("WOULD RETRACT");
			//~ retractActuator();
		}			
	}
	
}
