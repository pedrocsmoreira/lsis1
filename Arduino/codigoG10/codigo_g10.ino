#define LDR A0

#define L1 A1
#define L2 A2
#define L3 A3
#define L4 A4
#define L5 A5

#define PWM1 3
#define PWM2 5
#define DIR1 4
#define DIR2 6

#define MA1 7
#define MA2 8
#define MB1 9
#define MB2 10

boolean start = false;

unsigned long startTime;
unsigned long endTime;

int mult[5];
int xmax[5] = {0, 0, 0, 0, 0};
int xmin[5] = {1023, 1023, 1023, 1023, 1023};

double val[5];
double xmin[5] = {81,66,87,81,68};
double xmax[5] = {978,976,982,982,972};
double cal[5];
double total = 0;

void setup(){
    Serial.begin(9600);

    pinMode(LDR, INPUT);

    pinMode(L1, INPUT);
    pinMode(L2, INPUT);
    pinMode(L3, INPUT);
    pinMode(L4, INPUT);
    pinMode(L5, INPUT);

    pinMode(PWM1, OUTPUT);
    pinMode(PWM2, OUTPUT);
    pinMode(DIR1, OUTPUT);
    pinMode(DIR2, OUTPUT);

    pinMode(MA1, INPUT_PULLUP);
    pinMode(MA2, INPUT_PULLUP);
    pinMode(MB1, INPUT_PULLUP);
    pinMode(MB2, INPUT_PULLUP);

    calibrar();
    startTime = 0;
    endTime = 0;
}

void loop(){
    while(!start){
        readLDR();
    }
    run();
}

void run(){
    startTime = millis();
    readLine();
    if(val[0] >= (xmax[0] - 100) && val[1] >= (xmax[1] - 100) && val[2] >= (xmax[2] - 100) && val[3] >= (xmax[3] - 100) && val[4] >= (xmax[4] - 100) ){
        stopping();
        endTime = millis();
        sendMessage();
        start = !start;
    }else if(total < -350){
        right();
    }else if(total > 350){
        left();
    }else {
        forward();
    }
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

void sendMessage(){
    unsigned long time = endTime - startTime;
    String message = maxspeed + "#" + time;
    Serial.write(message);
}

void calibrar(){
    startTime = millis();
    while((millis()-startTime) < 10000){
        mult[0] = analogRead(L1);
        mult[1] = analogRead(L2);
        mult[2] = analogRead(L3);
        mult[3] = analogRead(L4);
        mult[4] = analogRead(L5);
        for(int i = 0; i < 5; i++){
            if(mult[i] > xmax[i]){
                xmax[i] = mult[i];
            }else if(mult[i] < xmin[i]){
                xmin[i] = mult[i];
            }
        }
    }
}

void readLDR(){
    if(analogRead(LDR) > 750){
        start = !start;
    }
}

void readLine(){
  total = 0;
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