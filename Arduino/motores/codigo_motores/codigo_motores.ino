#include <util/atomic.h>

#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3
#define IR5 A4

#define PWM1 3
#define PWM2 5
#define DIR1 4
#define DIR2 6

#define ENCA1 8
#define ENCA2 9
#define ENCB1 10
#define ENCB2 11

double val[5];
double xmin[5] = {55,55,65,57,63};
double xmax[5] = {973,972,972,973,972};
double cal[5];
double total = 0;

void setup(){
  Serial.begin(9600);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);

  pinMode(ENCA1, INPUT_PULLUP);
  pinMode(ENCA2, INPUT_PULLUP);
  pinMode(ENCB1, INPUT_PULLUP);
  pinMode(ENCB2, INPUT_PULLUP);
}

void forward(){
    analogWrite(PWM1, 255);
    analogWrite(PWM2, 255);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
}

void left(){
    analogWrite(PWM1, 100);
    analogWrite(PWM2, 100);
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
}

void right(){
    analogWrite(PWM1, 100);
    analogWrite(PWM2, 100);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
}

void stopping(){
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
}

void loop(){
    forward();
    delay(200);
    Serial.print("ENCA - ");
    Serial.println(digitalRead(ENCA1));
    Serial.print("ENCA - ");
    Serial.println(digitalRead(ENCA2));
    Serial.print("ENCB - ");
    Serial.println(digitalRead(ENCB1));
    Serial.print("ENCB - ");
    Serial.println(digitalRead(ENCB2));
    delay(1000);
    Serial.print("ENCA - ");
    Serial.println(digitalRead(ENCA1));
    Serial.print("ENCA - ");
    Serial.println(digitalRead(ENCA2));
    Serial.print("ENCB - ");
    Serial.println(digitalRead(ENCB1));
    Serial.print("ENCB - ");
    Serial.println(digitalRead(ENCB2));
    delay(5000);
    
  /*
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  while(!start){
    readLDR();
  }
  readLine();
  Serial.println(total);
  if(total < 0){
    right();
  }else if(total > 0){
    left();
  }else {
    forward();
  }
  delay(10000);
  */
}

void readLine(){
  val[0] = analogRead(IR1);
  val[1] = analogRead(IR2);
  val[2] = analogRead(IR3);
  val[3] = analogRead(IR4);
  val[4] = analogRead(IR5);
  int n;
  for(n = 0; n < 5; n++){
    cal[n] = (val[n] - xmin[n])/(xmax[n] - xmin[n]) * 1000;
    total = total + (cal[n] * (n-2));
  }
}
