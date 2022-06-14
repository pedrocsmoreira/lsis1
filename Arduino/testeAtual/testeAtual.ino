#include <analogWrite.h>

#define IR1 4
#define IR2 35
#define IR3 34
#define IR4 36
#define IR5 39

#define PWM1 25
#define PWM2 16
#define DIR1 26
#define DIR2 27

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

  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
}

void motor(){
  Serial.println("MOTORES");
  analogWrite(PWM1, 255);
  analogWrite(PWM2, 255);
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
}

void parar(){
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
}

void loop(){
  Serial.println("LER LINHA");
  readLine();
  Serial.println("IR PRO MOTOR");
  motor();
  delay(1000);
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
