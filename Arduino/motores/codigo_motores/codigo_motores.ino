#define L1 A0
#define L2 A1
#define L3 A2
#define L4 A3
#define L5 A4

#define PWM1 3
#define PWM2 5
#define DIR1 4
#define DIR2 6

double val[5];
double xmin[5] = {55,55,65,57,63};
double xmax[5] = {973,972,972,973,972};
double cal[5];
double total = 0;

void setup(){
    Serial.begin(9600);
    pinMode(L1, INPUT);
    pinMode(L2, INPUT);
    pinMode(L3, INPUT);
    pinMode(L4, INPUT);
    pinMode(L5, INPUT);
    
    pinMode(PWM1, OUTPUT);
    pinMode(PWM2, OUTPUT);
    pinMode(DIR1, OUTPUT);
    pinMode(DIR2, OUTPUT);
}

void loop(){
    readLine();
    Serial.println(total);
    if(total < -150){
        right();
    }else if(total > 150){
        left();
    }else {
        forward();
    }
    delay(10000);
}

void forward(){
    analogWrite(PWM1, 255);
    analogWrite(PWM2, 255);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
}

void left(){
    analogWrite(PWM1, 255);
    analogWrite(PWM2, 255);
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
}

void right(){
    analogWrite(PWM1, 255);
    analogWrite(PWM2, 255);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
}

void stopping(){
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
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