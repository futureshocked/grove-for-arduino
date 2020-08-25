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

#include <U8g2lib.h>  // Install the U8g2 by searching it by name in the Library Manager.
                      // Documentation: https://github.com/olikraus/u8g2/wiki/u8g2reference

#include <NewPing.h>  // Learn about this library: https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);

#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 50 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600);
  u8g2.begin();
}

void loop() {
  print_sensor_readings();
  delay(50); // Experiment with this delay to see how quickly the Arduino can redraw.
}

void print_sensor_readings()
{
  // The height of the font used is 12

  // the positions of the labels and accelerometer values
  u8g2_uint_t x_position = 80;
  u8g2_uint_t y_position = 12;

  int distance     = sonar.ping_cm();
  Serial.print(distance);

  // Set the character arrays to contain the accelerometer values.
  char buffer_distance[7];
  dtostrf(distance, 3, 0, buffer_distance); // Learn about dtostrf at https://www.nongnu.org/avr-libc/user-manual/group__avr__stdlib.html#ga060c998e77fb5fc0d3168b3ce8771d42


  u8g2.firstPage();           // Using the firstPage / nextPage method.
                              // Advantage: much faster then the partial redraw method.
                              // Dissadvantage: must reset the whole screen every time.
  do {
    // draw the axis lines
    u8g2.drawHLine(0, 30, 128);
    u8g2.drawVLine(0, 0, 64);

    u8g2.setFont(u8g2_font_t0_18_tf); // This is a 18-point font

    // Print distance values
    u8g2.drawStr(x_position, y_position, buffer_distance);

    //Show object location using a circle
    if (distance > 0)
    {
      int dot_x = map(distance,0,MAX_DISTANCE,0,128);// The position of the disc on the y-axis depends on the y-axis acceleration.
      Serial.print(", ");
      Serial.println(dot_x);
      u8g2.drawDisc(dot_x,31,5);
    }
      else
    {
      u8g2.drawStr(10, 25, "No contact");
    }

    u8g2.setFont(u8g2_font_t0_12b_tf);
    u8g2.drawStr(80, 64,  "Sonar");

  } while ( u8g2.nextPage() );
}
