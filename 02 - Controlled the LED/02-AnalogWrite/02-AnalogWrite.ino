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

int ledPin = 3;      // LED connected to digital pin 3

void setup() {
  pinMode(ledPin, OUTPUT);  // sets the pin as output
}

void loop() {
  for (int brightness = 0; brightness < 255; brightness++)
  {
    analogWrite(ledPin, brightness);
    delay(10);
  }

  for (int brightness = 255; brightness > 0; brightness--)
  {
    analogWrite(ledPin, brightness);
    delay(10);
  }

}
