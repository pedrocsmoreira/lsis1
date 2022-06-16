#define L1 A1
#define L2 A2
#define L3 A3
#define L4 A4
#define L5 A5

int mult[150][5];
int xmax[5] = {0, 0, 0, 0, 0};
int xmin[5] = {100, 100, 100, 100, 100};

void setup() {
  Serial.begin(9600);
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  pinMode(L4, INPUT);
  pinMode(L5, INPUT);
}

void loop() {
    verMaior();
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
    delay(5000);
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
  int n;
  for(n = 0; n < 150; n++){
    mult[n][0] = analogRead(L1);
    mult[n][1] = analogRead(L2);
    mult[n][2] = analogRead(L3);
    mult[n][3] = analogRead(L4);
    mult[n][4] = analogRead(L5);
  }
}

void verMaior(){
  lerValores();
  int i, j;
  for(i = 0; i < 150; i++){
    for(j = 0; j < 5; j++){
      if(mult[i][j] > xmax[j]){
        xmax[j] = mult[i][j];
      }
    }
  }
}

void verMenor(){
  lerValores();
  int i, j;
  for(i = 0; i < 150; i++){
    for(j = 0; j < 5; j++){
      if(mult[i][j] < xmin[j]){
        xmin[j] = mult[i][j];
      }
    }
  }
}
