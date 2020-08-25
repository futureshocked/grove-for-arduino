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

int buzzerPin = 5;      // select the pin for the LED

void setup() {
  pinMode(buzzerPin, OUTPUT);  // declare the ledPin as an OUTPUT
  randomSeed(analogRead(1));
}

void loop() {
  int frequency = random(500,2000);       // Get a random frequency from 50 Hz to 2000 Hz
  int duration  = random(100,1000);        // Get a random duration from 20 ms to 50 ms
  tone(buzzerPin, frequency, duration);
  delay(200);
}
