#include <Dabble.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GamePad_MODULE

#define TRIG 9
#define ECHO 8

#define IR_RIGHT 5
#define IR_LEFT 4

#define leftMotor1 12 
#define leftMotor2 13
#define rightMotor1 10
#define rightMotor2 11

float pulse_width, distance;
bool mode = true; //true- bluetooth, false - follow

void setup() {
  Dabble.begin(9600); // Start Dabble communication at 9600 baud rate
  Serial.begin(9600);
  
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);

  pinMode(IR_RIGHT, INPUT);
  pinMode(IR_LEFT, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
}

// Functions to control the movement of the car
void moveForward() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}
void moveBackward() {
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  

}
void turnLeft() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  

}
void turnRight() {
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);

}
void stopMotors() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}
  
void sensorCtrl(){
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  pulse_width = pulseIn(ECHO, HIGH);
  distance = (pulse_width*.0343)/2;      //CM
  
  int rightValue = digitalRead(IR_RIGHT);
  int leftValue = digitalRead(IR_LEFT);

  if((distance > 1) && (distance < 10)){
    moveForward();
  }else if ((rightValue == LOW) && (leftValue == HIGH)){
    turnRight();
  }else if ((rightValue == HIGH) && (leftValue == LOW)){
    turnLeft(); 
  }else if (distance > 10){
    stopMotors();
  }
}

void loop() {
  Serial.println(distance);
  Dabble.processInput(); 
  
  if(GamePad.isCrossPressed()){
    mode = !mode;
    delay(1000);
  }
  
  if(mode == true){
    if (GamePad.isUpPressed()) { 
    moveForward();
  } else if (GamePad.isDownPressed()) { 
    moveBackward();
  } else if (GamePad.isLeftPressed()) { 
    turnLeft();
  } else if (GamePad.isRightPressed()){ 
    turnRight();
  }else { 
    stopMotors();
  }
  }
  else {
    sensorCtrl();
  }
  }
  
