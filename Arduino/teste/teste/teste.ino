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

int xmax[5] = {0, 0, 0, 0, 0};
int xmin[5] = {1023, 1023, 1023, 1023, 1023};
double val[5];
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
    /*
    while(!start){
        readLDR();
    }
    */
    run();
}

void run(){
    startTime = millis();
    readLine();
    if(val[0] >= (xmax[0] - 100) && val[1] >= (xmax[1] - 100) && val[2] >= (xmax[2] - 100) && val[3] >= (xmax[3] - 100) && val[4] >= (xmax[4] - 100) ){
        stopping();
        endTime = millis();
        //sendMessage();
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
    analogWrite(PWM1, 120);
    analogWrite(PWM2, 200);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
}

void right(){
    analogWrite(PWM1, 200);
    analogWrite(PWM2, 120);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
}

void stopping(){
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
}

void calibrar(){
    startTime = millis();
    while((millis()-startTime) < 10000){
        val[0] = analogRead(L1);
        val[1] = analogRead(L2);
        val[2] = analogRead(L3);
        val[3] = analogRead(L4);
        val[4] = analogRead(L5);
        for(int i = 0; i < 5; i++){
            if(val[i] > xmax[i]){
                xmax[i] = val[i];
            }else if(val[i] < xmin[i]){
                xmin[i] = val[i];
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
