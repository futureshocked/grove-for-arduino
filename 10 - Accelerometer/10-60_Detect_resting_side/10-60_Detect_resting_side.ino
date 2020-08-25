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
#include "LIS3DHTR.h"
#include <Wire.h>
LIS3DHTR<TwoWire> LIS; //IIC

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);


void setup() {
  Serial.begin(9600);

  LIS.begin(Wire, 0x19); //IIC init
  LIS.openTemp();  //If ADC3 is used, the temperature detection needs to be turned off.
  // We are using the I2C interface for the acceleration so it is possible
  // to get temperature readings.

  delay(10);
  LIS.setFullScaleRange(LIS3DHTR_RANGE_2G);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  LIS.setHighSolution(true); //High solution enable

  u8g2.begin();

}

void loop() {
  print_sensor_readings();
  delay(10); // Experiment with this delay to see how quickly the Arduino can redraw.
}

void print_sensor_readings()
{
  // The height of the font used is 12

  // the positions of the labels and accelerometer values
  u8g2_uint_t x_position_x = 66;
  u8g2_uint_t y_position_x = 8;

  u8g2_uint_t x_position_y = 0;
  u8g2_uint_t y_position_y = 30;

  u8g2_uint_t x_position_z = 0;
  u8g2_uint_t y_position_z = 8;

  u8g2_uint_t x_position_t = 85;
  u8g2_uint_t y_position_t = 64;

  float accel_x     = LIS.getAccelerationX();
  float accel_y     = LIS.getAccelerationY();
  float accel_z     = LIS.getAccelerationZ();
  float temperature = LIS.getTemperature();

  // Set the character arrays to contain the accelerometer values.
  char buffer_x[7];
  dtostrf(accel_x, 4, 2, buffer_x); // Learn about dtostrf at https://www.nongnu.org/avr-libc/user-manual/group__avr__stdlib.html#ga060c998e77fb5fc0d3168b3ce8771d42
  if (accel_x < 0)
  {
    buffer_x[5] = 'x';  // If the acceleartion is negative, the the value uses 4 symbols.
    buffer_x[6] = '\0'; // Because I have added the "x" character in the end of the array,
  } else                // I must use '\0' to manually null-terminate it.
  {                     // Read: https://www.arduino.cc/reference/en/language/variables/data-types/string/
    buffer_x[4] = 'x';  // If the acceleartion is positive, the the value uses 3 symbols.
    buffer_x[5] = '\0'; // Therefore, the "x" symbol must go in index 4 of the array.
  }
  char buffer_y[7];
  dtostrf(accel_y, 4, 2, buffer_y);
  if (accel_y < 0)
  {
    buffer_y[5] = 'y';
    buffer_y[6] = '\0';  // Because I have added the "y" character in the end of the array,
  } else                 // I must use '\0' to manually null-terminate it.
  {
    buffer_y[4] = 'y';
    buffer_y[5] = '\0';
  }

  char buffer_z[7];
  dtostrf(accel_z, 4, 2, buffer_z);
  if (accel_z < 0)
  {
    buffer_z[5] = 'z';
    buffer_z[6] = '\0';  // Because I have added the "z" character in the end of the array,
  } else                 // I must use '\0' to manually null-terminate it.
  {
    buffer_z[4] = 'z';
    buffer_z[5] = '\0';
  }
  char buffer_t[8];
  dtostrf(temperature, 4, 2, buffer_t);
  buffer_t[5] = char(0xB0);
  buffer_t[6] = 'C';  // Because I have added the "y" character in the end of the array,
  buffer_t[7] = '\0'; // I must use '\0' to manually null-terminate it.

  u8g2.firstPage();           // Using the firstPage / nextPage method.
                              // Advantage: much faster then the partial redraw method.
                              // Dissadvantage: must reset the whole screen every time.
  do {
    // draw the axis lines
    u8g2.drawHLine(0, 30, 128);
    u8g2.drawVLine(64, 0, 64);

    u8g2.setFont(u8g2_font_t0_12_tf); // This is a 12-point font

    // Print accelleration values
    u8g2.drawStr(x_position_x, y_position_x, buffer_x);
    u8g2.drawStr(x_position_y, y_position_y, buffer_y);
    u8g2.drawStr(x_position_z, y_position_z, buffer_z);

    // Print temperature value
    u8g2.drawStr(x_position_t, y_position_t, buffer_t);

    //Show animation using a circle
//    u8g2.drawDisc(64,32,5); // This will draw a circle at the center of the display.
    int dot_x = map(accel_x*100,-110,110,0,64); // The position of the disc on the x-axis depends on the x-axis acceleration.
    int dot_y = map(accel_y*100,-110,110,0,128);// The position of the disc on the y-axis depends on the y-axis acceleration.
    int dot_z = map(accel_z*100,-110,110,2,8);  // The size of the disc depends on the z-axis acceleration.
    u8g2.drawDisc(dot_y,dot_x,dot_z);

    // Which side is the Arduino on?
    int position_label_x = 110;
    int position_label_y = 30;
    u8g2.setFont(u8g2_font_courB24_tf);
    if (accel_y < -0.20)
      u8g2.drawStr(position_label_x, position_label_y,  "R");
    else if (accel_y > 0.20)
      u8g2.drawStr(position_label_x, position_label_y,  "L");
    else if (accel_x > 0.20)
      u8g2.drawStr(position_label_x, position_label_y,  "F");
    else if (accel_x < -0.20)
      u8g2.drawStr(position_label_x, position_label_y,  "B");
    else
      u8g2.drawStr(position_label_x, position_label_y,  "C");

    u8g2.setFont(u8g2_font_t0_12b_tf);
    u8g2.drawStr(0, 64,  "Accelerometer");

  } while ( u8g2.nextPage() );


}
