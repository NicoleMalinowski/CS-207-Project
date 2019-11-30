/*
  Nicole Malinowski
  200 261 547
  CS 207 Project
  Fall 2019

  This code is for a temperature sensing catapult that launches when it gets warm. There is also a colour changing LED that gives you a warning when the cataoult is going to launch. 
  The LED starts at blue, changes to green as a warning, then to red when the cataoult launches. 
  Temperature zone are: 
        Blue LED from absolute zero to blue2green threshold
        Green LED from blue2gree threshold to green2launch threshold 
        Red LED for anything above green2launch threshold
        * Note that thresholds are in celcius
        * Note that thresholds when temperature are decreasing are 0.5 degrees less so light is stable

  The servo position of 0 is assocaited with a released catapult
  The servo position of 90 is associated with holding the catapult down.

   After catapult has launched reload catapult and push button to have servo move back into position to hold catapult down.


   Wiring:
   For push button:
      On one side of button have 5 volts connected to flyback diode to button
      On other side of button  (same side of breadboard) have 10,000 ohm resister to ground
      On other side of button (opposite side of breadboard) have wire to didgital pin 2
   For temperature sensor:
      Temperature sensor has three prongs. Set up with flat side with writing closer to Arduino.
      Left prong (when looking at writing on sensor) goes to 5 volts
      Middle prong goes to analog pin 0
      Right prong goes to ground
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



//set up colour changing LED pins and temp sensor and button pin
const int redPin = 11;
const int greenPin = 12;
const int bluePin = 13;
int tempPin = 0;
const int buttonPin = 2;  //button used to move servo to lock position

int buttonState = 0;  //initial state of button
//Adjust this threshold as necessary.
// When button is clicked to reset servo is sometimes causes spike in temp sensor readings so the threshold needs to be more than a few numbers above the normal room temp
// thresholds are in celcius
int blue2green = 20; // threshold to change LED from blue to green
int green2launch = 22; //threshold value of sensor at which the catapult launches and LED changes from green to red (change this to fit your needs)
int tempSensor;  // value read in from temperature sensor
float celcius; 
float celciusOld; 

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
  tempSensor = analogRead(tempPin);
  celciusOld = celcius; 
  celcius = (tempSensor/1023.00*5.00*100.00)-50.00; 
  Serial.print(celcius);
  Serial.println();

// changing light to green if above the threshold
if (celcius > blue2green and celcius<green2launch-0.5) { 
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  }

// if temperature falls back into blue LED zone then switch back. 
if (celcius < blue2green-0.5) { 
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }

// launch catapult and change LED to red if abive threshold
  if (celcius > green2launch) { //if pressure sensor value is above threshold...
    myservo.write(0); //...move servo back to neutral position
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }

// Reset cataoult with button
  if (buttonState == HIGH) { 
    myservo.write(90); 
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }


  delay(100);

}
