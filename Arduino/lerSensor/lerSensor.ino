#define L1
#define L2
#define L3
#define L4
#define L5

int mult[150][5];
int[5] val;

void setup() {
  Serial.begin(9600);
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  pinMode(L4, INPUT);
  pinMode(L5, INPUT);
}

void loop() {
  Serial.println("O que pretende ler? (1/2)");
  Serial.println("1 - Ler maiores");
  Serial.println("2 - Ler menores");
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
  }
  if(incomingByte == 1){
    val = lerMaior();
    Serial.print(val[0]);
    Serial.print(" - ");
    Serial.print(val[1]);
    Serial.print(" - ");
    Serial.print(val[2]);
    Serial.print(" - ");
    Serial.print(val[3]);
    Serial.print(" - ");
    Serial.println(val[4]);
  }else if(incomingByte == 2){
    val = lerMenor();
    Serial.print(val[0]);
    Serial.print(" - ");
    Serial.print(val[1]);
    Serial.print(" - ");
    Serial.print(val[2]);
    Serial.print(" - ");
    Serial.print(val[3]);
    Serial.print(" - ");
    Serial.println(val[4]);
  }
  incomingByte = 0;
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

int[5] verMaior(){
  lerValores();
  int i, j;
  int[5] xmax = {0; 0; 0; 0; 0};
  for(i = 0; i < 150; i++){
    for(j = 0; j < 5; j++){
      if(mult[i][j] > xmax[j]){
        xmax[j] = mult[i][j];
      }
    }
  }
  return xmax;
}

int[5] verMenor(){
  lerValores();
  int i, j;
  int[5] xmin = {10000; 10000; 10000; 10000; 10000};
  for(i = 0; i < 150; i++){
    for(j = 0; j < 5; j++){
      if(mult[i][j] < xmin[j]){
        xmin[j] = mult[i][j];
      }
    }
  }
  return xmin;
}