 //arduino pins, need change
#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3
#define IR5 A4

#define PWM1 3
#define PWM2 5
#define DIR1 4
#define DIR2 6

#define ADATA1
#define ADATA2
#define BDATA1
#define BDATA2

bool start = false;

int startTime;
int finalTime;

int proportional;
int derivative; 
int integral;
int position;
int last_proportional;
int power_error;

const char* ssid = "LSIS";
const char* password = "lsis2122";
const char* mqtt_server = "192.168.0.1";

const char* topic = "lsis1";
const char* subtopic = "G10";

//precisa de valores definidos
int Kp = 0;
int Ki = 0;
int Kd = 0;

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

  pinMode(ADATA1, INPUT_PULLUP);
  pinMode(ADATA2, INPUT_PULLUP);
  pinMode(BDATA1, INPUT_PULLUP);
  pinMode(BDATA1, INPUT_PULLUP);

  setupWIFI();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
}

void motor(){
  analogWrite(PWM1, 120);
  analogWrite(PWM2, 120);
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, HIGH);
}

void loop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  while(start){
    readLDR();
  }
  startTime = millis
  readLine();
  pid();
  motor();
  if(val[0] <= (xmin[0] + 50) && val[1] <= (xmin[1] + 50) && val[2] <= (xmin[2] + 50) && val[3] <= (xmin[3] + 50) && val[4] <= (xmin[4] + 50)){
    finalTime = millis() - startTime();
    message();
    start = false;
  }
}

void readLDR(){
  if(analogRead(LDR) <= 400){
    start = !start;
  }
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

void pid(){
  proportional = position - 2000;
  derivative = proportional - last_proportional;
  integral += proportional;

  last_proportional = proportional;
  
  power_error = proportional * Kp + integral * Ki + derivative * Kd;
}

void message(){

}
