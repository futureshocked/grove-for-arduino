

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

void setup() {
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R2);   // 180 degree clockwise rotation
//  u8g2.setDisplayRotation(U8G2_R0); // No rotation, landscape
  //u8g2.setFont(u8g2_font_tenthinnerguys_t_all); // Find more fonts at https://github.com/olikraus/u8g2/wiki/fntlistall
  //u8g2.setFont(u8g2_font_emoticons21_tr);                                 // They are listed by font height in pixels.
  u8g2.setFont(u8g2_font_helvB24_tf);
  u8g2.drawStr(20, 30, "Hello World!");
  u8g2.sendBuffer();

}

void loop()
{

}
