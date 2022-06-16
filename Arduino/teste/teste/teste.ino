#define ldr A5

void setup() {
  Serial.begin(9600);
  pinMode(ldr, INPUT);
}

void loop() {
  Serial.println(analogRead(ldr));
  delay(1000);
}
