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

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int positions[] = {20, 40, 80, 30, 60, 120, 140, 180, 130, 160, 90, 5, 45, 78};

void setup() {
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  myservo.write(5);
  delay(100);
  Serial.begin(9600);
}

void loop() {
  // I use sizeof to get the size of the array in bytes.
  // Because the array in this example contains int, and each int has two bytes,
  // I divide the sizeoff value by two to get the actual number of values
  // in the array.
  for (int pos = 0; pos < sizeof(positions)/2; pos++)
  {
    Serial.print(pos);
    Serial.print(": ");
    Serial.println(positions[pos]);
    myservo.write(positions[pos]);       // sets the servo position
    delay(200);                           // waits for the servo to get there
  }
  Serial.println("----------");
  delay(1000);
}
