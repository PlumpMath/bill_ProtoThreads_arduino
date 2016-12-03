#define PT_USE_TIMER
#define PT_USE_SEM

#include "pt.h"
static struct pt thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8;
unsigned char i;

int laststate[8] = {1};

const int M11 = 30;
const int M12 = 31;
const int M21 = 32;
const int M22 = 33;
const int M31 = 34;
const int M32 = 35;
const int M41 = 36;
const int M42 = 37;
const int BUZZER = 5;
const int LAO1 = 22;
const int LAO2 = 23;
const int BREAK = 24;
const int LLED = 25;
const int RLED = 26;
const int R1 = 46;
const int R2 = 47;
const int R3 = 48;
const int R4 = 49;
const int R5 = 50;
const int R6 = 51;
const int R7 = 52;
const int R8 = 53;
const int R9 = 45;
const int LAI = A0;
const int LFW = 10;
const int RFW = 9;
const int RRW = 8;
const int LEFTHIGH = 100;
const int RIGHTHIGH = 10;

int isChange(int pinNum);

void setup() {
  //Set Hardware
  Serial.begin(115200);

  pinMode(13, OUTPUT);
  pinMode(M11, INPUT);
  pinMode(M12, INPUT);
  pinMode(M21, INPUT);
  pinMode(M31, INPUT);
  pinMode(M32, INPUT);
  pinMode(M41, INPUT);
  pinMode(M42, INPUT);
  pinMode(LAI, INPUT);
  pinMode(LAO1, OUTPUT);
  pinMode(LAO2, OUTPUT);
  pinMode(BREAK, OUTPUT);
  pinMode(LLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(R9, OUTPUT);
  pinMode(LFW, OUTPUT);
  pinMode(RFW, OUTPUT);
  pinMode(RRW, OUTPUT);

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
  while (1)
  {
    //if forward btn is pressed
    if ( digitalRead(M11) == 0 ) {

      digitalWrite(BREAK, LOW);
      digitalWrite(R3, LOW);
      digitalWrite(R4, LOW);
      digitalWrite(R9, LOW);
      PT_TIMER_DELAY(pt, 10);
      digitalWrite(R1, HIGH);
      digitalWrite(R2, HIGH);
      digitalWrite(R5, HIGH);
      digitalWrite(R6, HIGH);
      digitalWrite(R7, HIGH);
      digitalWrite(R8, HIGH);
      PT_TIMER_DELAY(pt, 10);
      digitalWrite(R3, HIGH);
      digitalWrite(R4, HIGH);
      digitalWrite(R9, HIGH);
      Serial.println("go forward");

      //no right & left turn
      if ( digitalRead(M21) == 1 && digitalRead(M22) == 1 ) {

        analogWrite(LFW, 255);
        analogWrite(RFW, 255);
        analogWrite(RRW, 255);
      }

    }
    PT_YIELD(pt); //Check the other events.
  }

  PT_END(pt);
}

//backward
static int thread2_entry(struct pt *pt)
{
  PT_BEGIN(pt);
  while (1)
  {
    if (digitalRead(M12) == 0) {

      digitalWrite(BREAK, LOW);
      digitalWrite(R3, LOW);
      digitalWrite(R4, LOW);
      digitalWrite(R9, LOW);
      PT_TIMER_DELAY(pt, 10);
      digitalWrite(R1, LOW);
      digitalWrite(R2, LOW);
      digitalWrite(R5, LOW);
      digitalWrite(R6, LOW);
      digitalWrite(R7, LOW);
      digitalWrite(R8, LOW);
      PT_TIMER_DELAY(pt, 10);
      digitalWrite(R3, HIGH);
      digitalWrite(R4, HIGH);
      digitalWrite(R9, HIGH);
      Serial.println("go back");

      //no right & left turn
      if ( digitalRead(M21) == 1 && digitalRead(M22) == 1 ) {

        analogWrite(LFW, 150);
        analogWrite(RFW, 150);
        analogWrite(RRW, 150);
      }
    }

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//turn left
static int thread3_entry(struct pt *pt)
{
  PT_BEGIN(pt);
  while (1)
  {

    if (digitalRead(M21) == 0) {

      Serial.println("turn left");
      LAplace = analogRead(LAI);
      LAplace = map(LAplace, 0, 1024, 0, 255);
      if (LAplace < LEFTHIGH) {
        digitalWrite(LAO1, LOW);
        digitalWrite(LAO2, HIGH);
      }
      else {
        digitalWrite(LAO1, LOW);
        digitalWrite(LAO2, LOW);
      }

      //if backward
      if (state1 == 0) {
        analogWrite(LFW, 200);
        analogWrite(RFW, 210);
        analogWrite(RRW, 200);
      }

      if (state2 == 0) {
        analogWrite(LFW, 150);
        analogWrite(RFW, 160);
        analogWrite(RRW, 150);
      }
    }

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//turn right
static int thread4_entry(struct pt * pt)
{
  PT_BEGIN(pt);
  while (1)
  {
    if (digitalRead(M22) == 0) {

      Serial.println("turn right");
      LAplace = analogRead(LAI);
      if (LAplace > RIGHTHIGH) {
        digitalWrite(LAO2, LOW);
        digitalWrite(LAO1, HIGH);
      }
      else {
        digitalWrite(LAO1, LOW);
        digitalWrite(LAO2, LOW);
      }

      //if backward
      if (state1 == 0) {
        analogWrite(LFW, 210);
        analogWrite(RFW, 200);
        analogWrite(RRW, 200);
      }

      if (state2 == 0) {
        analogWrite(LFW, 160);
        analogWrite(RFW, 150);
        analogWrite(RRW, 150);
      }
    }

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//alarm
static int thread5_entry(struct pt * pt)
{
  PT_BEGIN(pt);
  while (1)
  {
    Serial.println("alarm");

    //backward buzz or alarm
    if ( digitalRead(M12) == 0 || digitalRead(M31) == 0 ) {

      tone(5, 100);
      PT_TIMER_DELAY(pt, 1000);
      tone(5, 36000);
      PT_TIMER_DELAY(pt, 1000);
    }

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//left sign
static int thread6_entry(struct pt * pt)
{
  PT_BEGIN(pt);
  while (1)
  {

    if ( digitalRead(M41) == 0 ) {

      Serial.println("left sign");
      digitalWrite(LLED, HIGH);
      PT_TIMER_DELAY(pt, 10000);
      digitalWrite(LLED, LOW);
      PT_TIMER_DELAY(pt, 10000);
    }

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//right sign
static int thread7_entry(struct pt * pt)
{
  PT_BEGIN(pt);
  while (1)
  {
    if ( digitalRead(M42) == 0 ) {

      Serial.println("right sign");
      digitalWrite(RLED, HIGH);
      PT_TIMER_DELAY(pt, 10000);
      digitalWrite(RLED, LOW);
      PT_TIMER_DELAY(pt, 10000);
    }

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}

//break
static int thread8_entry(struct pt * pt)
{
  PT_BEGIN(pt);
  while (1)
  {
    if ( digitalRead(M32) == 0 ) {

      Serial.println("break");
      digitalWrite(BREAK, LOW);
      digitalWrite(R3, LOW);
      digitalWrite(R4, LOW);
      digitalWrite(R9, LOW);

      digitalWrite(LAO1, LOW);
      digitalWrite(LAO2, LOW);
    }

    PT_YIELD(pt); //Check the other events.
  }
  PT_END(pt);
}


///\[para] pinNum
///\ [return] if isChange, return 1
int isChange(int pinNum) {

  if ( digitalRead(pinNum) != laststate[pinNum - 30] && laststate[pinNum - 30] == 1 ) {
    Serial.print("the state of pin");
    Serial.print(pinNum);
    Serial.print(" is ");
    Serial.println(digitalRead(pinNum));
    laststate[i] = digitalRead(pinNum);

    return 1;
  }
  else if ( digitalRead(pinNum) != laststate[pinNum - 30] && laststate[pinNum - 30] == 0 )
    laststate[pinNum - 30] = digitalRead(pinNum);

  return 0;
}

void loop() {
  //Check each thread by priority

  thread1_entry(&thread1);
  thread2_entry(&thread2);
  thread3_entry(&thread3);
  thread4_entry(&thread4);
  thread5_entry(&thread5);
  thread6_entry(&thread6);
  thread7_entry(&thread7);
  thread8_entry(&thread8);

}
