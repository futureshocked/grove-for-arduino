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

// U8g2lib reference: https://github.com/olikraus/u8g2/wiki/u8g2reference

#include <U8g2lib.h>  // Install the U8g2 by searching it by name in the Library Manager.
                      // Documentation: https://github.com/olikraus/u8g2/wiki/u8g2reference

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(             U8G2_R0,
                                          /* clock=*/ SCL,
                                          /* data=*/  SDA,
                                          /* reset=*/ U8X8_PIN_NONE);

int counter = 1;

void setup() {
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R2);   // 180 degree clockwise rotation
//  u8g2.setDisplayRotation(U8G2_R0); // 180 degree clockwise rotation
  u8g2.setFont(u8g2_font_tenthinnerguys_t_all); // Find more fonts at https://github.com/olikraus/u8g2/wiki/fntlistall
                                      // They are listed by font height in pixels.
  u8g2.drawStr(0, 40, "Counting numbers...");

  Serial.begin(9600);

}

void loop() {
  draw_number(counter);
  //print_number(counter);

  delay(250);
  counter++;
}

void draw_number(int number)
{
  //  u8g2.drawStr(60, 45, counter);
  char buffer[3];
  dtostrf(counter, 3, 0, buffer);
  u8g2_uint_t x_position = 0;
  u8g2_uint_t y_position = 20;
  int font_height = 18;
  u8g2.setFont(u8g2_font_courB18_tn);
  u8g2.setDrawColor(0);
  u8g2.drawBox(x_position,y_position - font_height,55,20);
//  u8g2.drawStr(x_position, y_position, "    ");  // clear the position of the next number
    u8g2.setDrawColor(1);
  u8g2.drawStr(x_position, y_position, buffer); // draw the number
  u8g2.sendBuffer();                            // print the number
}

void print_number(int number)
{
  u8g2_uint_t x_position = 0;
  u8g2_uint_t y_position = 20;
  int font_height = 18;

  u8g2.setFont(u8g2_font_courB18_tn);
  u8g2.setDrawColor(0);
  u8g2.drawBox(x_position,y_position - font_height,55,20);
  u8g2.setDrawColor(1);
  u8g2.setCursor(x_position, y_position);
  u8g2.print(number);
  u8g2.sendBuffer();                          // print the number
}
