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
#include <Wire.h>

void bright_or_dark(int light_value);

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(             U8G2_R0,
                                          /* clock=*/ SCL,
                                          /* data=*/  SDA,
                                          /* reset=*/ U8X8_PIN_NONE);

int flashlight_pin = 2;
int light_sensor_pin = A6;

void setup() {
  pinMode(light_sensor_pin, INPUT);
  pinMode(flashlight_pin , OUTPUT);
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R2);   // 180 degree clockwise rotation
  u8g2.setFont(u8g2_font_tenthinnerguys_t_all); // Find more fonts at https://github.com/olikraus/u8g2/wiki/fntlistall
                                      // They are listed by font height in pixels.
  u8g2.drawStr(0, 40, "Light intensity");
  u8g2.drawStr(0, 60, "0: Dark 750: Bright");

  Serial.begin(9600);

}

void loop() {
  int light_intensity = analogRead(light_sensor_pin);
  print_number(light_intensity);
  bright_or_dark(light_intensity);
  delay(250);
}

void print_number(int number)
{
  u8g2_uint_t x_position = 0;
  u8g2_uint_t y_position = 20;
  int font_height = 18;

  u8g2.setFont(u8g2_font_logisoso18_tf);
  u8g2.setDrawColor(0);
  u8g2.drawBox(x_position,y_position - font_height,55,20);
  u8g2.setDrawColor(1);
  u8g2.setCursor(x_position, y_position);
  u8g2.print(number);
  u8g2.sendBuffer();                          // print the buffer
}

void bright_or_dark(int light_value)
{

  if (light_value > 700)
  {
    print_light_status("Bright");
    digitalWrite(flashlight_pin , LOW);  // Turn off the flashlight
  }
  else
  {
    print_light_status("Dark");
    digitalWrite(flashlight_pin , HIGH);  // Turn on the flashlight
  }
}

void print_light_status(String light_status)
{
  u8g2_uint_t x_position = 60;
  u8g2_uint_t y_position = 20;
  int font_height = 14;

  u8g2.setFont(u8g2_font_fub14_tf);
  u8g2.setDrawColor(0);
  u8g2.drawBox(x_position,y_position - font_height,65,20);
  u8g2.setDrawColor(1);
  u8g2.setCursor(x_position, y_position);
  u8g2.print(light_status);
  u8g2.sendBuffer();                          // print the buffer
}
