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

int sensorPin = A0;    // Potentiometer sensor
int ledPin = 4;      // select the pin for the LED

void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  Serial.begin(9600);
}

void loop() {

  int sensorValue   = analogRead(sensorPin);                // read the value from the sensor
  int delay_msec    = map(sensorValue, 0, 1023, 100, 1000); // Map the sensor input value
                                                            // (ranges from 0 to 1023) to
                                                            // milliseconds (from 100 to 2000).
  Serial.print("Raw sensor value: ");
  Serial.print(sensorValue);
  Serial.print(", mapped value: ");
  Serial.println(delay_msec);
  digitalWrite(ledPin, HIGH);
  delay(delay_msec);
  digitalWrite(ledPin, LOW);
  delay(delay_msec);
}
