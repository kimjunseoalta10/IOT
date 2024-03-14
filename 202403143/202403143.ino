int i=0;

void setup() {
  Serial.begin(9600);
  for(i;i<10;i++){
    Serial.print("for i :");
    Serial.print(i);
    Serial.println("Hi EDI");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
