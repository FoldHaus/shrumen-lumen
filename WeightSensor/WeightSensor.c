/* 
 gurov was here, use this code, or don't, whatever, I don't care. If you see a giant bug with a billion legs, please let me know so it can be squashed

*/

#include <wiringPi.h>
#include <stdio.h>
#include <sched.h>
#include <string.h>
#include <stdlib.h>

#define CLOCK_PIN	5
#define DATA_PIN	4
#define N_SAMPLES	10
#define SPREAD		10

#define SCK_ON  digitalWrite(CLOCK_PIN, HIGH) //setSCK(1) //(GPIO_SET0 = (1 << CLOCK_PIN))
#define SCK_OFF digitalWrite(CLOCK_PIN, LOW) //setSCK(0) //(GPIO_CLR0 = (1 << CLOCK_PIN))
#define DT_R    digitalRead(DATA_PIN) //getData() //(GPIO_IN0  & (1 << DATA_PIN))

void           reset_converter(void);
unsigned long  read_cnt(long offset, int argc);
void           set_gain(int r);
void           setHighPri (void);

void setHighPri (void)
{
  struct sched_param sched ;

  memset (&sched, 0, sizeof(sched)) ;

  sched.sched_priority = 10 ;
  if (sched_setscheduler (0, SCHED_FIFO, &sched))
    printf ("Warning: Unable to set high priority\n") ;
}

void setup_gpio()
{
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

int main(int argc, char **argv)
{
  if(wiringPiSetup() == -1)
	exit(1);

  int i, j;
  long tmp=0;
  long tmp_avg=0;
  long tmp_avg2;
  long offset=0;
  float filter_low, filter_high;
  float spread_percent = SPREAD / 100.0 /2.0;
  int b;
  int nsamples=N_SAMPLES;
  long samples[nsamples];
  for(i = 0; i < nsamples; i++){
	samples[i] = 0;
  }

  printf("Starting...\n");

  if (argc == 2) {
   offset = atol(argv[1]);
  }

  printf("Offset: %d\n", offset);

  //setHighPri();
  setup_gpio();

  j=0;

  printf("Starting smapling...\n");



  while(1){
	usleep(1000 * 1000);
	long sampl = read_cnt(offset, argc) / 10000;
	for(i = nsamples - 1; --i >= 1;){
		samples[i] = samples[i-1];
	}

	int pastAve = 0;
	for(i = nsamples - 1; i >= nsamples / 2; i--){
		pastAve += samples[i];
	}
	pastAve /= (nsamples - 1) - (nsamples / 2);
	printf("Past Average: %d  (%d -> %d)\n", pastAve, samples[1], sampl);

	int distFromAve = abs(sampl - pastAve);
	int distFromLast = abs(sampl - samples[1]);
	int lastNoise = abs(samples[1] - samples[2]);

	if(distFromAve > 10 && distFromLast > 10){
		printf("CHANGE!!!!\n");
	}

	samples[0] = sampl;
  }

  // get the dirty samples and average them
  for(i=0;i<nsamples;i++) {
  	// reset_converter();
  	samples[i] = read_cnt(offset, argc);
	printf("Got sample: %d\n", samples[i]);
  	tmp_avg += samples[i];
  }

  tmp_avg = tmp_avg / nsamples;

  tmp_avg2 = 0;
  j=0;

  filter_low =  (float) tmp_avg * (1.0 - spread_percent);
  filter_high = (float) tmp_avg * (1.0 + spread_percent);

  printf("%d %d\n", (int) filter_low, (int) filter_high);

  for(i=0;i<nsamples;i++) {
	if ((samples[i] < filter_high && samples[i] > filter_low) || 
            (samples[i] > filter_high && samples[i] < filter_low) ) {
		tmp_avg2 += samples[i];
	        j++;
	}
  }

  if (j == 0) {
    printf("No data to consider\n");
    exit(255);

  }
  printf("%d\n", (tmp_avg2 / j) - offset);
}


void reset_converter(void) {
	SCK_ON;
	usleep(60);
	SCK_OFF;
	usleep(60);
}

void set_gain(int r) {
	int i;

// r = 0 - 128 gain ch a
// r = 1 - 32  gain ch b
// r = 2 - 63  gain ch a

	while( DT_R ); 

	for (i=0;i<24+r;i++) {
		SCK_ON;
		SCK_OFF;
	}
}


unsigned long read_cnt(long offset, int argc) {
	long count;
	int streak;
	int streakmax;
	int i;
	int b;

  count = 0;

  while( DT_R );

  for(i=0;i<24	; i++) {
	SCK_ON;
        if (DT_R > 0 ) {
		count++;
	}
        SCK_OFF;
        count = count << 1;
  }

  SCK_ON;
  SCK_OFF;

//if (count & 0x800000) {
//	count |= (long) ~0xffffff;
//}

// if things are broken this will show actual data
  return (count - offset);
}


