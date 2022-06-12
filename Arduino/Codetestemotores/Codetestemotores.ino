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

#define ADATA1
#define ADATA2
#define BDATA1
#define BDATA2

const char* ssid = "LSIS";
const char* password = "lsis2122";
const char* mqtt_server = "192.168.0.1";

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

  pinMode(ADATA1, INPUT_PULLUP);
  pinMode(ADATA2, INPUT_PULLUP);
  pinMode(BDATA1, INPUT_PULLUP);
  pinMode(BDATA2, INPUT_PULLUP);

  setupWIFI();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  attachInterrupt(digitalPinToInterrupt(PWMA), readEncoder,RISING);
  attachInterrupt(digitalPinToInterrupt(PWMB), readEncoder,RISING);
}

void left(){
  analogWrite(PWMA, 40);
  analogWrite(PWMB, 40);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void right(){
  analogWrite(PWMA, 40);
  analogWrite(PWMB, 40);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void forward(){
  analogWrite(PWMA, 120);
  analogWrite(PWMB, 120);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void braking(){
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);
}



void loop(){
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
