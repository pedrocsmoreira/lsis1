#include <analogWrite.h>

#define PWM1 39
#define PWM2 36
#define DIR1 14
#define DIR2 12

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup(){
    pinMode(DIR1, OUTPUT);
    pinMode(DIR2, OUTPUT);

    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(PWM1, ledChannel);
    ledcAttachPin(PWM2, ledChannel);
}

void loop(){
    ledcWrite(PWM1, 255);
    ledcWrite(PWM2, 255);
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
}
