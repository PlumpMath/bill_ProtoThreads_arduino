#define PT_USE_TIMER
#define PT_USE_SEM

#include "pt.h"
static struct pt thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8;
int state1, state2, state3, state4, state5, state6, state7;
int flag1, flag2, flag3, flag4, flag5, flag6, flag7;

//Front wheel
const int LFM1 = 30;
const int LFM2 = 31;
const int LFEN = 32;
const int RFEN = 33;
const int RFM1 = 34;
const int RFM2 = 35;
//Back wheel
const int BM1 = 36;
const int BM2 = 37;
const int BEN = 38;
//liner actor
const int LAEN = 39;
const int LAM1 = 40;
const int LAM2 = 41;
//lights
const int LLight = 22;
const int RLight = 23;
const int BreakLight = 24;
//speed
const int LFSpeedCtrl = 10;
const int RFSpeedCtrl = 9;
const int BSpeedCtrl = 8;
const int Buzzer = 5;

void setup() {
  //Set Hardware
  Serial.begin(9600);

  pinMode(LFM1, OUTPUT);
  pinMode(LFM2, OUTPUT);
  pinMode(LFEN, OUTPUT);
  pinMode(RFEN, OUTPUT);
  pinMode(RFM1, OUTPUT);
  pinMode(RFM2, OUTPUT);

  pinMode(BM1, OUTPUT);
  pinMode(BM2, OUTPUT);
  pinMode(BEN, OUTPUT);

  pinMode(LAEN, OUTPUT);
  pinMode(LAM1, OUTPUT);
  pinMode(LAM2, OUTPUT);

  pinMode(LLight, OUTPUT);
  pinMode(RLight, OUTPUT);
  pinMode(BreakLight, OUTPUT);

  pinMode(LFSpeedCtrl, OUTPUT);
  pinMode(RFSpeedCtrl, OUTPUT);
  pinMode(BSpeedCtrl, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  flag1 = 0;
  flag2 = 0;
  flag3 = 0;
  flag4 = 0;
  flag5 = 0;
  flag6 = 0;
  flag7 = 0;

  //disable en of wheel
  digitalWrite(LFEN, HIGH);
  digitalWrite(RFEN, HIGH);
  digitalWrite(BEN, HIGH);

  digitalWrite(LAEN, HIGH);

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

    //forward enable
    if (state1 == 1 && !flag1) {

      flag1 = 1;

      Serial.println("enable forward");

      //disable en of wheel
      digitalWrite(LFEN, HIGH);
      digitalWrite(RFEN, HIGH);
      digitalWrite(BEN, HIGH);

      digitalWrite(LFM1, LOW);
      digitalWrite(LFM2, LOW);
      digitalWrite(RFM1, LOW);
      digitalWrite(RFM2, LOW);
      digitalWrite(BM1, LOW);
      digitalWrite(BM2, LOW);
      analogWrite(LFSpeedCtrl, 255);
      analogWrite(RFSpeedCtrl, 255);
      analogWrite(BSpeedCtrl, 255);

      PT_TIMER_DELAY(pt, 10);

      //enable en of wheel
      digitalWrite(LFEN, LOW);
      digitalWrite(RFEN, LOW);
      digitalWrite(BEN, LOW);

      //shutdown lights
      digitalWrite(BreakLight, LOW);
    }

    //forward disable
    else if (state1 == 0 && flag1) {
      flag1 = 0;

      Serial.println("disable forward");

      digitalWrite(LFEN, HIGH);
      digitalWrite(RFEN, HIGH);
      digitalWrite(BEN, HIGH);

      digitalWrite(BreakLight, HIGH);
    }

    PT_YIELD(pt); //Check the other events.
  }

  PT_END(pt);
}

//backward
static int thread2_entry(struct pt *pt)
{
  PT_BEGIN(pt);
  while (1) {
    if (state2 == 1 && !flag2) {

      flag2 = 1;

      Serial.println("enable forward");

      //disable en of wheel
      digitalWrite(LFEN, HIGH);
      digitalWrite(RFEN, HIGH);
      digitalWrite(BEN, HIGH);

      digitalWrite(LFM1, HIGH);
      digitalWrite(LFM2, HIGH);
      digitalWrite(RFM1, HIGH);
      digitalWrite(RFM2, HIGH);
      digitalWrite(BM1, HIGH);
      digitalWrite(BM2, HIGH);
      analogWrite(LFSpeedCtrl, 200);
      analogWrite(RFSpeedCtrl, 200);
      analogWrite(BSpeedCtrl, 200);

      PT_TIMER_DELAY(pt, 10);

      //enable en of wheel
      digitalWrite(LFEN, LOW);
      digitalWrite(RFEN, LOW);
      digitalWrite(BEN, LOW);

      //shutdown lights
      digitalWrite(BreakLight, LOW);
    }

    else if (state2 == 0 && flag2) {

      flag2 = 0;

      Serial.println("disable backward");

      digitalWrite(LFEN, HIGH);
      digitalWrite(RFEN, HIGH);
      digitalWrite(BEN, HIGH);

      digitalWrite(BreakLight, HIGH);
    }

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//turn left
static int thread3_entry(struct pt *pt)
{
  int sensorValue;

  PT_BEGIN(pt);
  while (1) {
    if (state3 == 1 && !flag3) {

      sensorValue = analogRead(A0);
      sensorValue = map(sensorValue, 0, 1023, 0, 49);

      Serial.print("turn left ");
      Serial.println(sensorValue);

      if (sensorValue >= 0)
      {

        flag3 = 1;
        digitalWrite(LAEN, HIGH);
        digitalWrite(LAM1, HIGH);
        digitalWrite(LAM2, HIGH);

        PT_TIMER_DELAY(pt, 10);

        digitalWrite(LAEN, LOW);
      }
    }

    else if (state3 == 0  && flag3) {

      flag3 = 0;
      digitalWrite(LAEN, HIGH);
    }

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//turn right
static int thread4_entry(struct pt * pt)
{
  int sensorValue;

  PT_BEGIN(pt);
  while (1) {
    if (state4 == 1 && !flag4) {

      sensorValue = analogRead(A0);
      sensorValue = map(sensorValue, 0, 1023, 0, 49);

      Serial.print("turn right ");
      Serial.println(sensorValue);

      if (sensorValue <= 49)
      {

        flag4 = 1;
        digitalWrite(LAEN, HIGH);
        digitalWrite(LAM1, LOW);
        digitalWrite(LAM2, LOW);

        PT_TIMER_DELAY(pt, 10);

        digitalWrite(LAEN, LOW);
      }
    }

    else if (state4 == 0  && flag4) {

      flag4 = 0;
      digitalWrite(LAEN, HIGH);
    }

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

        Serial.println(p);
        if ( 11 == p ) state1 = 1;
        else if ( 12 == p ) {
          state1 = 0;
          state2 = 0;
        }
        else if ( 21 == p ) state2 = 1;
        else if ( 22 == p ) {
          state3 = 0;
          state4 = 0;
        }
        else if ( 31 == p ) state3 = 1;
        else if ( 41 == p ) state4 = 1;
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
