
// Written by Ryan Jones

#include <Servo.h>

const int buttonPin = 2;  //button used to move servo to lock position, attached to digital input 2
//int pressurePin = 0; // pressure sensor to trigger release of catapult, attached to analog input 0
int tempPin = 0; 
int buttonState = 0;  //initial state of button
int threshold=192; //threshold value of sensor at which the catapult launches (change this to fit your needs)
int temp; 

Servo myservo;  // create a servo object to control a servo
int position = 0; //servo starts at neutral position

void setup() {
Serial.begin(9600); //display serial input (reads pressure sensor value - adjust threshold accordingly)
pinMode(buttonPin, INPUT); //make the button pin an input pin
myservo.attach(9); //servo attached to pin 9 to hold/fire catapult
}

void loop() {
buttonState = digitalRead(buttonPin); //read value of button
//pressurePin=analogRead(pressurePin); //read value of pressure sensor
temp = analogRead(tempPin);
Serial.print(temp); 
Serial.println(); 
delay(100); 
//temp= 0; 
if(buttonState == HIGH) { //if button pressed...
myservo.write(90); //...move servo 90 degrees (change this number to fit your personal use)
}

if(temp > threshold) { //if pressure sensor value is above threshold...
myservo.write(0); //...move servo back to neutral position 
}
}
