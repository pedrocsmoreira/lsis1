#define PWMA 3
#define AIN2 12
#define AIN1 11
#define BIN1 9
#define BIN2 8
#define PWMB 5

void setup(){
    Serial.begin(9600);
    pinMode(PWMA, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
}

void loop(){
    /*Serial.println("Drive");
    drive();
    delay(5000);
    Serial.println("Stop");
    stop();
    delay(5000);
    Serial.println("Drive");
    drive();
    delay(5000);
    Serial.println("Brake");
    brake();
    delay(100000000);*/
    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
}

void drive(){
    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
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
