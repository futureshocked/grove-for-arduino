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


int sensorPin = A2;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(sensorPin, INPUT);             // Set the potentiometer pin as INPUT
  Serial.begin(9600);                   // Start the serial monitor connection at 9600 bauds
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);  // Get the potentiometer value
  Serial.println(sensorValue);          // Print the potentiometer value
  delay(100);                           // Wait for 100 milliseconds
}
