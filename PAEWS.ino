#include <Servo.h> //include the servo library
using namespace std;
//Make 2 servo objects
Servo hortServo;
int trigPin = 2;
int echoPin = 3;
int trigMeteorPin = 11;
int echoMeteorPin = 12;
int redLEDPin = 5;
int yellowLEDPin = 6;
int greenLEDPin = 7;
int secondsDetecting = 0;
float distance = 0;
float meteorDistance = 0;
int position = 1;
bool disaster = false;

void setup() {
//put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigMeteorPin, OUTPUT);
  pinMode(echoMeteorPin, INPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
}
void loop() {
// put your main code here, to run repeatedly:
  secondsDetecting = 0;
  disaster = detect();
  Serial.println(disaster);
  digitalWrite(yellowLEDPin, LOW);
  switch (position) {
  case 1:
    position+=1;
    hortServo.write(180);
    break;
  case 2:
    position+=1;
    hortServo.write(150);
    break;
  case 3:
    position+=1;
    hortServo.write(120);
    break;
  case 4:
    position+=1;
    hortServo.write(90);
    break;
  case 5:
    position+=1;
    hortServo.write(60);
    break;
  case 6:
    position+=1;
    hortServo.write(30);
    break;
  case 7:
    position = 1;
    hortServo.write(0);
    break;
  }
  delay(500);
}
float getDistance() {
  float echoTime; //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance; //variable to store the distance calculated from the echo time
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  echoTime = pulseIn(echoPin, HIGH); //use the pulsein command to see how long it takes for the pulse to bounce back to the sensor
  calculatedDistance = echoTime / 148.0; //calculate the distance of the object that reflected the  pulse (half the bounce time multiplied by the speed of sound)
  return calculatedDistance; //send back the distance that was calculated
}
float getMeteorDistance() {
  float echoTime; //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance; //variable to store the distance calculated from the echo time
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigMeteorPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigMeteorPin, LOW);
  echoTime = pulseIn(echoMeteorPin, HIGH); //use the pulsein command to see how long it takes for the pulse to bounce back to the sensor
  calculatedDistance = echoTime / 148.0; //calculate the distance of the object that reflected thepulse (half the bounce time multiplied by the speed of sound)
  return calculatedDistance; //send back the distance that was calculated
}
bool detect() {
  for (int i = 0; i < 10; i+=1) {
    distance = getDistance();
    meteorDistance = getMeteorDistance();
    Serial.print(meteorDistance); //print the distance that was measured
    Serial.println(" km"); //print units after the distance
    if (distance <= 3 || meteorDistance <= 30) {
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(yellowLEDPin, HIGH);
      hortServo.detach();
      secondsDetecting+=1;
      delay(1000);
    } else {
      digitalWrite(redLEDPin, LOW);
      digitalWrite(yellowLEDPin, LOW);
      digitalWrite(greenLEDPin, HIGH);
      hortServo.attach(9);
      return false;
     break;
  }
}
  digitalWrite(redLEDPin, HIGH);
  return true;
}
