#define L1 A1
#define L2 A2
#define L3 A3
#define L4 A4
#define L5 A5

int mult[150][5];
int xmax[5] = {0, 0, 0, 0, 0};
int xmin[5] = {1023, 1023, 1023, 1023, 1023};

void setup() {
  Serial.begin(9600);
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  pinMode(L4, INPUT);
  pinMode(L5, INPUT);
}

void loop() {
    lerValores();
    Serial.println("LER MAIORES");
    Serial.print(xmax[0]);
    Serial.print(" - ");
    Serial.print(xmax[1]);
    Serial.print(" - ");
    Serial.print(xmax[2]);
    Serial.print(" - ");
    Serial.print(xmax[3]);
    Serial.print(" - ");
    Serial.println(xmax[4]);
    verMenor();
    Serial.println("LER MENORES");
    Serial.print(xmin[0]);
    Serial.print(" - ");
    Serial.print(xmin[1]);
    Serial.print(" - ");
    Serial.print(xmin[2]);
    Serial.print(" - ");
    Serial.print(xmin[3]);
    Serial.print(" - ");
    Serial.println(xmin[4]);
    delay(5000);
}

void lerValores(){
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