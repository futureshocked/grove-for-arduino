/*  Arduino for Beginners with Grove
 *
 * This code is part of a course from Tech Explorations.
 * For information about this course, please see
 *
 * https://techexplorations.com/so/grove/
 *
 * For information on hardware components and the wiring needed to
 * run this sketch, please see the relevant lecture in the course.
 *
 *
 *  Created by Peter Dalmaris
 *
 */
 

int ledPin    = 3;      // select the pin for the LED
int buttonPin = 2;      // Set the pin for the button.

void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  pinMode(buttonPin, INPUT); // declare the buttonPin as an INPUT
  Serial.begin(9600);
}

void loop() {
  int buttonValue = digitalRead(buttonPin);

  if (buttonValue == HIGH)        // If the button is pressed, its value is HIGH
  {
    control_led(buttonValue);
    //digitalWrite(ledPin, buttonValue);  // Turn the LED on
  }
  else
  {
    control_led(buttonValue);
    //digitalWrite(ledPin, buttonValue);  // Turn the LED off
  }
}

void control_led(int state)
{
  digitalWrite(ledPin, state);
}
