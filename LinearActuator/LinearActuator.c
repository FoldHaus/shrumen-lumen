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
#define MIN_DELAY_TIME 5000

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


int state = 99;
void setup_gpio()
{
  pinMode(DIRECTION_PIN, OUTPUT);
  pinMode(PWM_PIN, PWM_OUTPUT);
}

int getState(int data){
	//~ char cmd[200];
	//~ sprintf(cmd,
		//~ "curl -X GET %s",
		//~ GET_URL);
	//~ int state = cJSON_GetObjectItem(cmd,"state")->valueint;
	//~ printf("cmd: %s\n", cmd);
	//~ system(cmd);
	//~ snprintf(cmd, sizeof(cmd), "curl -X GET %s 2>&1", GET_URL);
	//~ printf(cmd);
	//~ 
	//~ FILE *curlGET = popen(cmd, "r");
	//~ printf(fgets);
	//~ char buf[256];
	//~ if(fgets(buf, sizeof(buf), curlGET) == 0) {
		//~ printf("It was zero...\n");
	//~ }
	//~ while(fgets(buf, sizeof(buf), curlGET) != 0) {
		//~ printf("Entered into the loop");
		//~ printf(buf);
	//~ }
	//~ pclose(curlGET);
}

void retract() {
	//~ stop();
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

void stopStuff() {
	printf("Stopping...\n");
	pwmWrite(PWM_PIN, 0);
}

int main(int argc, char **argv)
{
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
		
		printf("RES: %s\n", s.ptr);
		cJSON * json = cJSON_Parse(s.ptr);
		state = cJSON_GetObjectItem(json, "state")->valueint;
		printf("StateVal: %s\n", state);
		free(s.ptr);

		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	//Setup WiringPi w/ GPIO pins
	//~ if(wiringPiSetupGpio() == -1)
		//~ exit(1);
	
	// Set the pins to the correct output types.
	//~ setup_gpio();
	//~ 
	//~ while(1) {
		//~ if(state == 1) {
			//~ extend();
		//~ }
		//~ else if(state == 0) {
			//~ stop();
		//~ }
		//~ else if (state == -1){
			//~ retract()
		//~ }			
	//~ }
}
