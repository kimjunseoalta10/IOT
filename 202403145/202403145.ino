void setup() {
  Serial.begin(9600);
  pinMode(5,INPUT_PULLUP);
  pinMode(3,OUTPUT);
}

void loop() {
  int button = digitalRead(5);
  if(button==0){
    digitalWrite(3,HIGH);
  }
  else{
    digitalWrite(3,LOW);
  }
}
