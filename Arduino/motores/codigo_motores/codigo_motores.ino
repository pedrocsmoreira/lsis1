#include <util/atomic.h>


#define L1 A0
#define L2 A1
#define L3 A2
#define L4 A3
#define L5 A4

#define PWMA 3
#define PWMB 5
#define AIN1 7
#define AIN2 8
#define BIN1 6
#define BIN2 4

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

  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);

  pinMode(ENCA1, INPUT_PULLUP);
  pinMode(ENCA2, INPUT_PULLUP);
  pinMode(ENCB1, INPUT_PULLUP);
  pinMode(ENCB2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCA1), readEncoder,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCB1), readEncoder,RISING);
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
    Serial.println(digitalRead(ENCA1));
    Serial.println(digitalRead(ENCA2));
    Serial.println(digitalRead(ENCB1));
    Serial.println(digitalRead(ENCB1));
    delay(200);
    Serial.println(digitalRead(ENCA1));
    Serial.println(digitalRead(ENCA2));
    Serial.println(digitalRead(ENCB1));
    Serial.println(digitalRead(ENCB1));
    delay(200);
    
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

void readLDR(){
  if(analogRead(LDR) > ){
    start = !start;
  }
}

void readLine(){
  val[0] = analogRead(L1);
  val[1] = analogRead(L2);
  val[2] = analogRead(L3);
  val[3] = analogRead(L4);
  val[4] = analogRead(L5);
  int n;
  for(n = 0; n < 5; n++){
    cal[n] = (val[n] - xmin[n])/(xmax[n] - xmin[n]) * 1000;
    total = total + (cal[n] * (n-2));
  }
}
