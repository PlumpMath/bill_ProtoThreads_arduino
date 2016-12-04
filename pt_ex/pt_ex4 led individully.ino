#define PT_USE_TIMER
#define PT_USE_SEM

#include "pt.h"
static struct pt thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8;
int state1, state2, state3, state4, state5, state6, state7;

void recive();

void setup() {
  //Set Hardware
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  //Initialize the Threads
  PT_INIT(&thread1);
  PT_INIT(&thread2);
  PT_INIT(&thread3);
  PT_INIT(&thread4);
  PT_INIT(&thread5);
  PT_INIT(&thread6);
  PT_INIT(&thread7);
  PT_INIT(&thread8);

}

//forward
static int thread1_entry(struct pt *pt)
{
  PT_BEGIN(pt);
  while (1) {
    if (state1 == 1)
      digitalWrite(2, HIGH);
    else
      digitalWrite(2, LOW);

    PT_YIELD(pt); //Check the other events.
  }

  PT_END(pt);
}

//backward
static int thread2_entry(struct pt *pt)
{
  PT_BEGIN(pt);
  while (1) {
    if (state2 == 1)
      digitalWrite(3, HIGH);
    else
      digitalWrite(3, LOW);

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//turn left
static int thread3_entry(struct pt *pt)
{
  PT_BEGIN(pt);
  while (1) {
    if (state3 == 1)
      digitalWrite(4, HIGH);
    else
      digitalWrite(4, LOW);

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//turn right
static int thread4_entry(struct pt * pt)
{
  static int LAplace;
  PT_BEGIN(pt);
  while (1) {
    if (state4 == 1)
      digitalWrite(5, HIGH);
    else
      digitalWrite(5, LOW);

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//alarm
static int thread5_entry(struct pt * pt)
{
  PT_BEGIN(pt);
  while (1) {
    if (state5 == 1)
      digitalWrite(6, HIGH);
    else
      digitalWrite(6, LOW);

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//left sign
static int thread6_entry(struct pt * pt)
{
  PT_BEGIN(pt);
  while (1) {
    if (state6 == 1)
      digitalWrite(7, HIGH);
    else
      digitalWrite(7, LOW);

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//right sign
static int thread7_entry(struct pt * pt)
{
  PT_BEGIN(pt);
  while (1) {
    if (state7 == 1)
      digitalWrite(8, HIGH);
    else
      digitalWrite(8, LOW);

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//This is the received subroutine, it mainly receives data from Bluetooth and changes
//the global Boolean variable to open or close the other subroutine in the main loop
static int thread8_entry(struct pt * pt) {

  PT_BEGIN(pt);
  while (1)
  {
    while (Serial.available() > 0) {
      int p = Serial.parseInt();
      if (Serial.read() == 'X') {

        if ( 11 == p ) state1 = 1;
        else if ( 12 == p ) state1 = 0;
        else if ( 21 == p ) state2 = 1;
        else if ( 22 == p ) state2 = 0;
        else if ( 31 == p ) state3 = 1;
        else if ( 32 == p ) state3 = 0;
        else if ( 41 == p ) state4 = 1;
        else if ( 42 == p ) state4 = 0;
        else if ( 51 == p ) state5 = 1;
        else if ( 52 == p ) state5 = 0;
        else if ( 61 == p ) state6 = 1;
        else if ( 62 == p ) state6 = 0;
        else if ( 71 == p ) state7 = 1;
        else if ( 72 == p ) state7 = 0;
      }
    }

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

void loop() {
  //Check each thread by priority

  thread8_entry(&thread8);
  thread1_entry(&thread1);
  thread2_entry(&thread2);
  thread3_entry(&thread3);
  thread4_entry(&thread4);
  thread5_entry(&thread5);
  thread6_entry(&thread6);
  thread7_entry(&thread7);

}
