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

#include "ServoEasing.h"  // Instal via the library manager. See https://github.com/ArminJo/ServoEasing
#include <U8g2lib.h>      // Install the U8g2 by searching it by name in the Library Manager.
                          // Documentation: https://github.com/olikraus/u8g2/wiki/u8g2reference
#include <Wire.h>

ServoEasing Servo1;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int pos_raw;    // variable to read the value from the analog pin


U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(             U8G2_R0,
                                          /* clock=*/ SCL,
                                          /* data=*/  SDA,
                                          /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // attaches the servo on pin 9 to the servo object
  if (Servo1.attach(6) == INVALID_SERVO) {
        Serial.println(F("Error attaching servo"));
    }
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R2);   // 180 degree clockwise rotation
  u8g2.setFont(u8g2_font_tenthinnerguys_t_all); // Find more fonts at https://github.com/olikraus/u8g2/wiki/fntlistall
                                      // They are listed by font height in pixels.
  u8g2.drawStr(0, 40, "Servo position");

  Serial.begin(9600);
  Servo1.setSpeed(20);  // Set the speed at which the servo will move. You can change this in the loop.
  Servo1.write(5);      // Reset the servo position.
  Servo1.setSpeed(40);
}

void loop() {
  pos_raw = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  int pos_degrees = map(pos_raw, 0, 1023, 5, 180);     // scale it to use it with the servo (value between 0 and 180)
  print_number(pos_degrees);
  Servo1.startEaseTo(pos_degrees);                 // sets the servo position according to the scaled value.this call is non-blocking.
  Servo1.update();
}

void print_number(int number)
{
  u8g2_uint_t x_position = 0;
  u8g2_uint_t y_position = 20;
  int font_height = 18;

  u8g2.setFont(u8g2_font_timB18_tf);
  u8g2.setDrawColor(0);
  u8g2.drawBox(x_position,y_position - font_height,55,20);
  u8g2.setDrawColor(1);
  u8g2.setCursor(x_position, y_position);
  u8g2.print(number);
  u8g2.print(char(0xB0));   // This or one of the next two lines can print the degrees symbol.
//  u8g2.print(char(176));  // Use this technique to print any symbol that belongs to a TTF.
//  u8g2.write(0xB0);       // See https://github.com/olikraus/u8g2/wiki/fntgrpadobex11 for more symbols.
  u8g2.sendBuffer();        // print the buffer
}
