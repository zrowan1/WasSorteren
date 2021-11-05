#include <Arduino.h>
#include <Servo.h>

#define S0 9
#define S1 8
#define S2 11
#define S3 10
#define sensorOut 12
#define buzzer 4

Servo leftDoor;
Servo rightDoor;

int redColorValue;
int greenColorValue;
int blueColorValue;

enum WashColor {Dark, White, Color};

WashColor sortedWashColor;

void chooseColor()
{
  int frequency = 0;

  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 25,72,255,0);

  redColorValue = frequency;

  delay(50);

  ///////////////

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 30,90,255,0);

  greenColorValue = frequency;

  delay(50);

  ///////////////

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 25,70,255,0);

  blueColorValue = frequency;
 
  delay(50);
}

void chooseWash()
{
  if (redColorValue < 20 && greenColorValue < 20 && blueColorValue < 20)
  {
    sortedWashColor = Dark;
//  Serial.println("Dit hoort bij de donkere was");
    delay(1000);
  }
  else if (redColorValue > 240 && greenColorValue > 240 && blueColorValue > 240)
  {
    sortedWashColor = White;
//  Serial.println("Dit hoort bij de witte was");
    delay(1000);
  }
  else
  {
    sortedWashColor = Color;
//  Serial.println("Dit hoort bij de gekleurde was");
    delay(1000);
  }
}

void changeLeftDoorPosition(int angle)
{
  leftDoor.write(angle);
}
void changeRightDoorPosition(int angle)
{
  rightDoor.write(angle);
}

void resetDoorPositions()
{
  leftDoor.write(90);
  rightDoor.write(90);
}





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(sensorOut, INPUT);


  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  leftDoor.attach(2);
  rightDoor.attach(4);

  leftDoor.write(90);
  rightDoor.write(90);


}

void loop() {
  // put your main code here, to run repeatedly:

  chooseColor();

  chooseWash();

  switch (sortedWashColor)
  {
    case White:
    Serial.println("WIT");
    delay(1000);
    // beide deuren open zodat het in het midden door kan
    leftDoor.write(0);
    rightDoor.write(180);
    delay(1500);
    resetDoorPositions();
    delay(1000);
    break;

    case Dark:
    Serial.println("DONKER");
    delay(1000);
    leftDoor.write(120);
    rightDoor.write(100);
    delay(1500);
    resetDoorPositions();
    delay(1000);
    break;

    case Color:
    Serial.println("KLEUR");
    delay(1000);
    leftDoor.write(180);
    rightDoor.write(0);
    delay(1500);
    resetDoorPositions();
    delay(1000);
    break;
  }

}