/*
  Nicole Malinowski
  200 261 547
  CS 207 Project
  Fall 2019

  This code is for a catapult that launches if the temperature read is above some threshold.

  The servo position of 0 is assocaited with a released catapult
  The servo position of 90 is associated with holding the catapult down.

   After catapult has launched reload catapult and push button to have servo move back into position to hold catapult down.


   Wiring:
   For push button:
      On one side of button have 5 volts
      On other side of button  (same side of breadboard) have 10,000 ohm resister to ground
      On other side of button (opposite side of breadboard) have wire to didgital pin 2
   For temperature sensor:
      Temperature sensor has three prongs. Set up with flat side with writing closer to Arduino.
      Left prong (when looking at writing on sensor) goes to 5 volts
      Middle prong goes to analog pin 0
      Right prong goes to a 10,000 ohm resister then to ground
   For servo:
      Servo has three coloured wires (yellow, red, and brown)
      Yellow wire goes to digital pin 9
      Red wire goes to 5 volts
      Brown wire goes to ground
    For colour changing LED:
      Colour changing LED has 4 legs. They are (in order) blue, green, ground, and red. The ground leg is the longest.
      Blue LED leg goes to digital pin 13
      Green LED leg does to digital pin 12
      Red LED leg goes to digital pin 11


   Original Code by Ryan Jones
   https://maker.pro/arduino/projects/arduino-servo-catapult
*/



#include <Servo.h>



//set up colour changing LED pins and temp sensor pin
const int redPin = 11;
const int greenPin = 12;
const int bluePin = 13;
int tempPin = 0;

const int buttonPin = 2;  //button used to move servo to lock position, attached to digital input 2
int buttonState = 0;  //initial state of button
//Adjust this threshold as necessary.
// When button is clicked to reset servo is sometimes causes spike in temp sensor readings so the threshold needs to be more than a few numbers above the normal room temp
int threshold = 189; //threshold value of sensor at which the catapult launches (change this to fit your needs)
int temp;  // value read in from temperature sensor

Servo myservo;  // create a servo object to control a servo
int position = 0; //servo starts at neutral position


void setup() {
  Serial.begin(9600); //display serial input (reads pressure sensor value - adjust threshold accordingly)
  pinMode(buttonPin, INPUT); //make the button pin an input pin
  myservo.attach(9); //servo attached to pin 9 to hold/fire catapult
  //Set LED pins to output mode
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // initialize LED to be blue
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

void loop() {
  buttonState = digitalRead(buttonPin); //read value of button
  temp = analogRead(tempPin);
  Serial.print(temp);
  Serial.println();



  if (temp > threshold) { //if pressure sensor value is above threshold...
    myservo.write(0); //...move servo back to neutral position
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }

  if (buttonState == HIGH) { //if button pressed...
    myservo.write(90); //...move servo 90 degrees (change this number to fit your personal use)
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }


  delay(100);

}
