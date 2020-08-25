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

int soundSensorPin = A2;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  long sum = 0;   // Learn about the long data type:
                  // https://www.arduino.cc/reference/en/language/variables/data-types/long/

  for (int i = 0; i < 32; i++)
  {
    sum += analogRead(soundSensorPin);
  }

  sum >>= 5;  // Learn about the bitshift right operator
              // https://www.arduino.cc/reference/en/language/structure/bitwise-operators/bitshiftright/

  Serial.println(sum);  // Instead of the serial monitor, open up the serial plotter.
                        // The plotter will show the sum value as a line plot.
                        // The line will spike when a loud sound is detected by the
                        // mic. Note the range of values when there is no ambient
                        // noise. Anything above that is a loud sound.
  delay(10);
}
