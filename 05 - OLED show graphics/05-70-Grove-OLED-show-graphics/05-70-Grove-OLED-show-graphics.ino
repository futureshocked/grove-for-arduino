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

int potentiometer_pin = 0;

void setup(void) {
  u8g2.begin();

  u8g2.setDisplayRotation(U8G2_R2);
}

void loop(void) {

  int pot_value = analogRead(potentiometer_pin);

  if (pot_value > 768 && pot_value < 1024 )
    draw_box();
  else if (pot_value > 512 && pot_value < 768)
    draw_circle();
  else if (pot_value > 255 && pot_value < 512)
    draw_lines();
  else
    draw_pixels();

}

void draw_box() {
  int random_x_1_1;
  int random_y_1_1;
  int random_x_1_2;
  int random_y_1_2;
  int random_x_2_1;
  int random_y_2_1;
  int random_x_2_2;
  int random_y_2_2;

  u8g2.setDrawColor(1); /* color 1 for the box */


  for (int outer_loop = 0; outer_loop < 3; outer_loop++)
  {
    u8g2.clearBuffer();

    for (int i = 0; i < 3; i++)
    {
      random_x_1_1 = random (1, 129);
      random_y_1_1 = random (1, 64);
      random_x_1_2 = random (1, 129);
      random_y_1_2 = random (1, 64);
      random_x_2_1 = random (1, 129);
      random_y_2_1 = random (1, 64);
      random_x_2_2 = random (1, 129);
      random_y_2_2 = random (1, 64);

      u8g2.drawBox(random_x_1_1, random_y_1_1, random_x_1_2, random_y_1_2);
      u8g2.drawRFrame(random_x_2_1, random_y_2_1, random_x_2_2, random_y_2_2, 5);

    }

    int random_title_x = random (1, 80);
    int random_title_y = random (10, 64);
    u8g2.setDrawColor(0); /* color 0 for the background*/
    u8g2.drawBox(random_title_x - 1, random_title_y - 10, 38, 11); // Y of this box starts at font height-1
    u8g2.setFont(u8g2_font_tenthinnerguys_t_all);  // font height: 9px
    u8g2.setDrawColor(1); /* color 1 for the text */
    u8g2.drawStr(random_title_x, random_title_y, "BOXES");

    u8g2.sendBuffer();
    delay(100);
  }

}

void draw_circle() {
  int random_x_1;
  int random_y_1;
  int random_radius_1;

  int random_x_2;
  int random_y_2;
  int random_radius_2;

  u8g2.setDrawColor(1); /* color 1 for the box */

  for (int outer_loop = 0; outer_loop < 3; outer_loop++)
  {
    u8g2.clearBuffer();

    for (int i = 0; i < 3; i++)
    {
      random_x_1 = random (1, 129);
      random_y_1 = random (1, 64);
      random_radius_1 = random (10, 25);
      random_x_2 = random (1, 129);
      random_y_2 = random (1, 64);
      random_radius_2 = random (10, 25);

      u8g2.drawCircle(random_x_1, random_y_1, random_radius_1, U8G2_DRAW_ALL); // Options: see https://github.com/olikraus/u8g2/wiki/u8g2reference#drawcircle

      u8g2.drawDisc(random_x_2, random_y_2, random_radius_2, U8G2_DRAW_ALL);
    }

    int random_title_x = random (1, 80);
    int random_title_y = random (10, 64);
    u8g2.setDrawColor(0); /* color 0 for the background*/
    u8g2.drawBox(random_title_x - 1, random_title_y - 10, 50, 11); // Y of this box starts at font height-1
    u8g2.setFont(u8g2_font_tenthinnerguys_t_all);  // font height: 9px
    u8g2.setDrawColor(1); /* color 1 for the text */
    u8g2.drawStr(random_title_x, random_title_y, "CIRCLES");

    u8g2.sendBuffer();
    delay(100);
  }

}


void draw_lines() {
  int random_x_1;
  int random_y_1;
  int random_x_2;
  int random_y_2;
  u8g2.setDrawColor(1); /* color 1 for the box */

  for (int outer_loop = 0; outer_loop < 5; outer_loop++)
  {
    u8g2.clearBuffer();

    for (int i = 0; i < 10; i++)
    {
      random_x_1 = random (1, 129);
      random_y_1 = random (1, 64);
      random_x_2 = random (1, 129);
      random_y_2 = random (1, 64);

      u8g2.drawLine(random_x_1, random_y_1, random_x_2, random_y_2);

    }

    int random_title_x = random (1, 80);
    int random_title_y = random (10, 64);
    u8g2.setDrawColor(0); /* color 0 for the background*/
    u8g2.drawBox(random_title_x - 1, random_title_y - 10, 50, 11); // Y of this box starts at font height-1
    u8g2.setFont(u8g2_font_tenthinnerguys_t_all);  // font height: 9px
    u8g2.setDrawColor(1); /* color 1 for the text */
    u8g2.drawStr(random_title_x, random_title_y, "LINES");

    u8g2.sendBuffer();
    delay(100);
  }

}

void draw_pixels() {
  // random pixels
  int random_x;
  int random_y;

  u8g2.setDrawColor(1); /* color 1 for the box */
  //  u8g2.setFont(u8g2_font_tenthinnerguys_t_all);


  for (int outer_loop = 0; outer_loop < 5; outer_loop++)
  {
    u8g2.clearBuffer();
    //    u8g2.drawStr(random (1,100),random (10,64), "PIXELS");
    for (int i = 0; i < 10; i++)
    {
      random_x = random (1, 129);
      random_y = random (1, 64);
      u8g2.drawPixel(random_x, random_y);
    }

    int random_title_x = random (1, 80);
    int random_title_y = random (10, 64);
    u8g2.setDrawColor(0); /* color 0 for the background*/
    u8g2.drawBox(random_title_x - 1, random_title_y - 10, 50, 11); // Y of this box starts at font height-1
    u8g2.setFont(u8g2_font_tenthinnerguys_t_all);  // font height: 9px
    u8g2.setDrawColor(1); /* color 1 for the text */
    u8g2.drawStr(random_title_x, random_title_y, "PIXELS");
    u8g2.sendBuffer();
    delay(100);
  }

}

void draw_triangle() {

}
