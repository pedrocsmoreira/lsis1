#include <analogWrite.h>

#define line1
#define line2
#define line3
#define line4
#define line5

#define PWMA 18
#define AIN2 19
#define AIN1 23
#define STBY 5
#define BIN1 13
#define BIN2 12
#define PWMB 14

#define BOUT1 27
#define BOUT2 16
#define AOUT1 17
#define AOUT2 25

#define LDR ..

mult[5] = {-2, 1, 0, 1, 2};
xmax[5] = {0, 4095, 4095, 4095, 4095};
xmin[5] = {4095, 0, 0, 0, 0};

boolean start = false;

float Kp = 25;
float Ki = 0;
float Kd = 15;

void setup(){
    Serial.begin(9600);
    pinMode(PWMA, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(STBY, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);

    pinMode(BOUT1, INPUT_PULLUP);
    pinMode(BOUT2, INPUT_PULLUP);
    pinMode(AOUT1, INPUT_PULLUP);
    pinMode(AOUT2, INPUT_PULLUP);

    pinMode(LDR, INPUT);

    stop();
}

void loop(){
    while(!start){
        readLDR();
    }



    if(l1 <= x && l2 <= x && l3 <= x && l4 <= x && l5 <= x){
        brake();
        stop();
    }else if(l1 => x && l2 => x && l3 => x && l4 => x && l5 => x){
        brake();
        stop();
    }else if(l1 <= x){
        left();
    }else if(l2 <= x){
        left();
    }else if(l4 <= x){
        right();
    }else if(l5 <= x){
        right();
    }else if(l3 <= x){
        drive();
    }
    start = false;
}

void readLDR(){
    if(analogRead(ldr)){
        start = !start;
    }
}

void readLine(){
    l1 = analogRead();
    l2 = analogRead();
    l3 = analogRead();
    l4 = analogRead();
    l5 = analogRead();
}

void drive(){
    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
}

void left(){
    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
}

void right(){
    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOw);
    digitalWrite(BIN2, HIGH);
}

void stop(){
    analogWrite(PWMA, 0);
    analogWrite(PWMB, 0);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
}

void brake(){
    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, HIGH);
}