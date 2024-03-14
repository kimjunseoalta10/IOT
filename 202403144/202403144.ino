int Led_pin=3;

void setup() {
  pinMode(Led_pin,OUTPUT);
}

void loop() {
  digitalWrite(Led_pin,HIGH);
  delay(1000);
  digitalWrite(Led_pin,LOW);
  delay(1000);

}
