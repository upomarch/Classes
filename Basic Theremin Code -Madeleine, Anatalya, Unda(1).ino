

//as the example project for the theremin mentions, 
//there is an incompatability with the timer of the tone and NewPing functions that will have to be adressed
//We will do this with including the package Newtone
//The following code was adapted from the a project 
//on the arduino project hub at the following link:
// https://create.arduino.cc/projecthub/jvmccall/ultrasonic-theremin-033d6f?ref=search&ref_id=theremin&offset=4

#include <NewTone.h>
#include <NewPing.h>
#include <SPI.h>
#define MIN_DISTANCE 35

//To control the volume 
NewPing sonar(5,6,35)

//For SPI
byte address = 0x00;
int CS =10;

int echo = 3;
int trigger =4;

int distance;
int PotValue;

unsigned long TimeResponse;
float distance2;
float tone1;

void setup() {
  //define the pins
  Serial.begin(9600)
  pinMode(trigger, OUTPUT); //this is the tone sensor
  pinMode(echo, INPUT);
  pinMode(CS, OUTPUT);
  SPI.begin();

  //In order to conveniently have the arduino emit a startup sound that will indicate it is on
  //we have the following
  digitalPotWrite(255);
  for (int i = 50; i <= 400; i++){
    pinMode(9,i);
      NewTone(9,i);
      delay(10);
  }
  delay(500);
  for (int i = 400; i >= 50;i--){
    pinMode(9, OUTPUT);
      NewTone(9,i);
      delay(10);
  }
  

}

void loop() {
  // this is for while the theremin is being operated
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10); //this creates a pulse for the theremin that will render is playable
  digitalWrite(trigger, LOW);
  TimeResponse = pulseIN(echo, HIGH); //how long it takes the sound to return to sensor 
  distance2 = TimeResponce/58; \\This is the distance in centemeters
  //We will now set the theremin to play a the tone we conversed from the distance
  if (distance2 < MIN_DISTANCE){
    tone1 = 50.0*pow(2,(distance2/12.0));
    pinMode(9, OUTPUT);
    NewTone(9,tone1);
  }
  else{
    pinMode(9, OUTPUT);
    NewTone(9,400);
  }

  distance =sonar.ping_cm();

  int PotValue = map(distance, 0, 35, 240, 255);

  if (distance==0){
    PotValue = 255;
  }

  digitalPotWrite(PotValue);
  delay(10);
}

int digitalPotWrite (int value){
  digitalWrite(CS, LOW);
  SPI.transer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
