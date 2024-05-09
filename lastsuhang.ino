#include <AFMotor.h>

#include <SoftwareSerial.h>
AF_DCMotor motor_L(1);
AF_DCMotor motor_R(4);

#define BT_RXD A5
#define BT_TXD A4
#define led1 A2
#define led2 A3

int TrigPin = A0;
int EchoPin = A1;
long duration,distance;

bool isStopped = false;

int f = 0;
bool ff=false;
int timee = 0;

int Lspeed = 170;
int Rspeed = 200;

SoftwareSerial BTSerial(BT_RXD,BT_TXD);

void setup() {
  // put your setup code here, to run once:
  motor_L.setSpeed(0);
  motor_L.run(RELEASE);
  motor_R.setSpeed(0);
  motor_R.run(RELEASE);
  pinMode(EchoPin,INPUT);
  pinMode(TrigPin,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);

  BTSerial.begin(9600);
}

void loop() {
  if(BTSerial.available()){
    char val = BTSerial.read();
    if(val=='f') {
      f=1;
      go_motor(170);
    }
    else if(val=='b') {
      f=2;
      back_motor(170);
    }
    else if(val=='r') {
      f=3;
      right_motor(170);
    }
    else if(val=='l') {
      f=4;
      left_motor(170);
    }
    else if(val=='s') {
      f=0;
      stop_motor();
    }
    else if(val=='o') {
      while(1){
        char val = BTSerial.read();
        Forward();
        Obstacle_Check();
        if(val =='j'){break;}
      }
    }
    else {
      f=0;
      stop_motor();
    }
  }
  if(f==1) {
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
  }
  if(f==2&&timee>30) {
    timee=0;
    if(ff) {
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    }
    else {
    digitalWrite(A2,LOW);
    digitalWrite(A3,LOW);
    }
    ff=!ff;
  }
  if(f==3&&timee>30) {
    timee=0;
    if(ff) {
      digitalWrite(A2,HIGH);
      digitalWrite(A3,LOW);
    }
    else {
      digitalWrite(A2,LOW);
    }
    ff=!ff;
  }
  if(f==4&&timee>30) {
    timee=0;
    if(ff) {
      digitalWrite(A2,LOW);
      digitalWrite(A3,HIGH);
    }
    else {
      digitalWrite(A3,LOW);
    }
    ff=!ff;
  }
  
  else if(!f) {
    digitalWrite(A2,LOW);
    digitalWrite(A3,LOW);
  }
  else {
    timee++;
  }
  delay(10);
}

void go_motor(uint8_t speedSet){
  motor_L.setSpeed(speedSet);
  motor_R.setSpeed(speedSet);
  motor_L.run(FORWARD);
  motor_R.run(FORWARD);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
}

void back_motor(uint8_t speedSet){
  motor_L.setSpeed(speedSet);
  motor_R.setSpeed(speedSet);
  motor_L.run(BACKWARD);
  motor_R.run(BACKWARD);
}

void left_motor(uint8_t speedSet){
  motor_L.setSpeed(speedSet);
  motor_R.setSpeed(speedSet);
  motor_L.run(BACKWARD);
  motor_R.run(FORWARD);

}

void right_motor(uint8_t speedSet){
  motor_L.setSpeed(speedSet);
  motor_R.setSpeed(speedSet);
  motor_L.run(FORWARD);
  motor_R.run(BACKWARD);
}

void stop_motor(){
  motor_L.run(RELEASE);
  motor_R.run(RELEASE);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
}


void Obstacle_Check() {
  int val = random(2);
  Distance_Measurement();
  delay(50);
  Serial.println(distance);
  while (distance < 300) {
    if (distance < 150) {
      Backward();
      delay(800);
      Stop();
      delay(50);
      Distance_Measurement();
      delay(100);
    } 
    else {
      if (val == 0) {
        Right();
        delay(400);
      } else if (val == 1) {
        Left();
        delay(400);
      }
      Distance_Measurement();
      delay(100);
    }
  }
}

void Distance_Measurement(){
  digitalWrite(TrigPin,LOW);
  delay(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  duration = pulseIn(EchoPin,HIGH);
  distance = ((float)(340*duration)/1000)/2;
  delay(50);
}

void Forward(){
  motor_L.run(FORWARD);
  motor_R.run(FORWARD);
  motor_L.setSpeed(Lspeed);
  motor_R.setSpeed(Rspeed);}

void Backward(){
  motor_L.run(BACKWARD);
  motor_R.run(BACKWARD);
  motor_L.setSpeed(Lspeed);
  motor_R.setSpeed(Rspeed);}

void Right(){
  motor_L.run(FORWARD);
  motor_R.run(BACKWARD);
  motor_L.setSpeed(Lspeed);
  motor_R.setSpeed(Rspeed*0.5);
}

void Left(){
  motor_L.run(BACKWARD);
  motor_R.run(FORWARD);
  motor_L.setSpeed(Lspeed*0.5);
  motor_R.setSpeed(Rspeed);}



void Stop(){
  motor_L.run(RELEASE);
  motor_R.run(RELEASE);
  motor_L.setSpeed(0);
  motor_R.setSpeed(0);}
