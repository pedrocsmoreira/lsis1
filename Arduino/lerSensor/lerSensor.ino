int mult[150][5];
int IR1 = A0;
int IR2 = A1;
int IR3 = A2;
int IR4 = A3;
int IR5 = A4;

int val1;
int val2; 
int val3;
int val4;
int val5;

int maior1 = 0;
int maior2 = 0;
int maior3 = 0;
int maior4 = 0;
int maior5 = 0;
int menor1 = 10000;
int menor2 = 10000;
int menor3 = 10000;
int menor4 = 10000;
int menor5 = 10000;

void setup() {
  Serial.begin(9600);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
}

void loop() {
  int n = 0; 
  for(n = 0; n < 150; n++){
    mult[n][0] = analogRead(IR1);
    mult[n][1] = analogRead(IR2);
    mult[n][2] = analogRead(IR3);
    mult[n][3] = analogRead(IR4);
    mult[n][4] = analogRead(IR5);
  }
  verMenor();
  delay(10000);
}

void verMaior(){
  int n;
  for(n = 0; n < 150; n++){
    if(mult[n][0] > maior1){
      maior1 = mult[n][0];
    }
    if(mult[n][1] > maior2){
      maior2 = mult[n][0];
    }
    if(mult[n][2] > maior3){
      maior3 = mult[n][0];
    }
    if(mult[n][3] > maior4){
      maior4 = mult[n][0];
    }
    if(mult[n][4] > maior5){
      maior5 = mult[n][0];
    }
  }
  Serial.println("MAIORES VALORES");
  Serial.print("IR1: ");
  Serial.print(maior1);
  Serial.print(" IR2: ");
  Serial.print(maior2);
  Serial.print(" IR3: ");
  Serial.print(maior3);
  Serial.print(" IR4: ");
  Serial.print(maior4);
  Serial.print(" IR5: ");
  Serial.println(maior5);
}

void verMenor(){
  int n;
  for(n = 0; n < 150; n++){
    if(mult[n][0] < menor1){
      menor1 = mult[n][0];
    }
    if(mult[n][1] < menor2){
      menor2 = mult[n][1];
    }
    if(mult[n][2] < menor3){
      menor3 = mult[n][2];
    }
    if(mult[n][3] < menor4){
      menor4 = mult[n][3];
    }
    if(mult[n][4] < menor5){
      menor5 = mult[n][4];
    }
  }
  Serial.println("MENORES VALORES");
  Serial.print("IR1: ");
  Serial.print(menor1);
  Serial.print(" IR2: ");
  Serial.print(menor2);
  Serial.print(" IR3: ");
  Serial.print(menor3);
  Serial.print(" IR4: ");
  Serial.print(menor4);
  Serial.print(" IR5: ");
  Serial.println(menor5);
}
