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

    stop()
}

void loop(){
    Serial.println("Drive");
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
    delay(100000000);
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