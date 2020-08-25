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

// We are using the Grove - OLED Display 0.96": 128×64 dot resolution display.
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(             U8G2_R0,
                                          /* clock=*/ SCL,
                                          /* data=*/  SDA,
                                          /* reset=*/ U8X8_PIN_NONE);

int potPinY = 0;
int potPinX = 2;

int newPotValueY = 0;
int newPotValueX = 0;

void setup() {
  pinMode(potPinY, INPUT);             // Set the potentiometer pin as INPUT
  pinMode(potPinX, INPUT);             // Set the potentiometer pin as INPUT
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R2);   // 180 degree clockwise rotation
  //u8g2.setDisplayRotation(U8G2_R0);     // No rotation, landscape
  u8g2.setFont(u8g2_font_tenthinnerguys_t_all); // Find more fonts at https://github.com/olikraus/u8g2/wiki/fntlistall
  // They are listed by font height in pixels.
  Serial.begin(9600);
}

void loop()
{
  int sensorValueY = analogRead(potPinY);  // Get the potentiometer value
  int sensorValueX = analogRead(potPinX);  // Get the potentiometer value
  int y_position = map(sensorValueY, 0, 1023, 0, 64); // The resolution of the display is 128x64
  int x_position = map(sensorValueX, 0, 1023, 0, 128); // The resolution of the display is 128x64
  u8g2.drawStr(x_position, y_position, "Hello World!");
  u8g2.sendBuffer();
  //delay(10);

  if (newPotValueY != sensorValueY || newPotValueX != sensorValueX)
  {
    newPotValueY = sensorValueY;
    newPotValueX = sensorValueX;

    Serial.print("X: ");
    Serial.print(newPotValueX);
    Serial.print(", Y: ");
    Serial.println(newPotValueY);

    u8g2.clearBuffer(); // Clear the display buffer
  }
}
