#define PT_USE_TIMER
#define PT_USE_SEM

#include "pt.h"
static struct pt thread1,thread2,thread3;
unsigned char i;

void setup() {
  //Set Hardware
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  
  //Initialize the Threads
  PT_INIT(&thread1);
  PT_INIT(&thread2);
  PT_INIT(&thread3);
}

//Blinky LED, 0.5Hz
static int thread1_entry(struct pt *pt)
{
  PT_BEGIN(pt);
  while (1)
  {
    digitalWrite(13,!digitalRead(13));
    PT_TIMER_DELAY(pt,1000);
    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//thread2
static int thread2_entry(struct pt *pt)
{
  PT_BEGIN(pt);
  while (1)
  {
    Serial.println("thread2");
    PT_TIMER_DELAY(pt,500);
    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

static int thread3_entry(struct pt *pt)
{
  PT_BEGIN(pt);
  while (1)
  {
    Serial.println("thread3");
    PT_TIMER_DELAY(pt,200);
    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

void loop() {
  //Check each thread by priority
  thread1_entry(&thread1);
  thread2_entry(&thread2);
  thread3_entry(&thread3);
}
