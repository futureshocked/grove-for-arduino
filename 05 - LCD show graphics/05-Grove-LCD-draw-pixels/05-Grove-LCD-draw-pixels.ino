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

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// See documentation for u8g2: https://github.com/olikraus/u8g2/wiki/u8g2reference

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();

  u8g2.setDisplayRotation(U8G2_R2);

  u8g2.setDrawColor(1); // the border of the box is white (i.e."on")

  // Uncomment the following lines one at a time to view a variety of lines.
//  u8g2.drawPixel(50,30);              // Draws a pixel
//  u8g2.drawPixel(55,30);              // Draws a pixel
//  u8g2.drawPixel(60,30);              // Draws a pixel
//  u8g2.drawPixel(65,30);              // Draws a pixel
//  u8g2.drawPixel(70,30);              // Draws a pixel
//  u8g2.drawPixel(75,30);              // Draws a pixel
//
//  u8g2.sendBuffer();  // Keep this line uncommented unless you are using draw_box.
}

void loop(void) {
    draw_pixels();
}

void draw_pixels(){
  // random pixels
  int random_x;
  int random_y;

  u8g2.setDrawColor(1); /* color 1 for the box */

  for (int outer_loop = 0; outer_loop< 5; outer_loop++)
  {
    u8g2.clearBuffer();
//    u8g2.drawStr(random (1,100),random (10,64), "PIXELS");
    for (int i = 0; i<10; i++)
    {
      random_x = random (1,129);
      random_y = random (1,64);
      u8g2.drawPixel(random_x, random_y);
    }

    int random_title_x = random (1,80);
    int random_title_y = random (10,64);
    u8g2.setDrawColor(0); /* color 0 for the background*/
    u8g2.drawBox(random_title_x - 1,random_title_y - 10,50,11); // Y of this box starts at font height-1
    u8g2.setFont(u8g2_font_tenthinnerguys_t_all);  // font height: 9px
    u8g2.setDrawColor(1); /* color 1 for the text */
    u8g2.drawStr(random_title_x,random_title_y, "PIXELS");
    u8g2.sendBuffer();
    delay(100);
  }
}
