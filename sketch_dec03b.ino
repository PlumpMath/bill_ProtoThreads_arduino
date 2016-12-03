const int M11 = 30;
const int M12 = 31;
const int M21 = 32;
const int M22 = 33;
const int M31 = 34;
const int M32 = 35;
const int M41 = 36;
const int M42 = 37;

int pin[8] = {30, 31, 32, 33, 34, 35, 36, 37};
int laststate[8] = {1};

void setup() {
  // put your setup code here, to run once:
  pinMode(M11, INPUT);
  pinMode(M12, INPUT);
  pinMode(M21, INPUT);
  pinMode(M31, INPUT);
  pinMode(M32, INPUT);
  pinMode(M41, INPUT);
  pinMode(M42, INPUT);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for (i = 0; i < 8; i++) {
    if ( digitalRead(pin[i]) != laststate[i] && laststate[i] == 1 ) {
      Serial.print("the state");
      Serial.print(i);
      Serial.print(" is ");
      Serial.println(digitalRead(pin[i]));
      laststate[i] = digitalRead(pin[i]);
    }
    else if ( digitalRead(pin[i]) != laststate[i] && laststate[i] == 0 )
      laststate[i] = digitalRead(pin[i]);
  }
}
