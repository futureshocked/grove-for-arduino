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

// This example use I2C.
// Find this library at https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR
#include "LIS3DHTR.h"
#include <Wire.h>
LIS3DHTR<TwoWire> LIS; // Using IIC (or I2C)

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  };
  //LIS.begin(WIRE); //IIC init dafault :0x18
  LIS.begin(Wire, 0x19); //IIC init
  LIS.openTemp();  //If ADC3 is used, the temperature detection needs to be turned off.
                  // We are using the I2C interface for the acceleration so it is possible
                  // to get temperature readings.

  delay(10);
  LIS.setFullScaleRange(LIS3DHTR_RANGE_2G);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_4G);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_8G);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_16G);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_1HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_10HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
  //LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_100HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_200HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_1_6KHZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_5KHZ);
  LIS.setHighSolution(true); //High solution enable
}
void loop()
{
  if (!LIS)
  {
    Serial.println("LIS3DHTR didn't connect.");
    while (1)
      ;
    return;
  }
  //3 axis
  Serial.print("x:"); Serial.print(LIS.getAccelerationX()); Serial.print("  ");
  Serial.print("y:"); Serial.print(LIS.getAccelerationY()); Serial.print("  ");
  Serial.print("z:"); Serial.println(LIS.getAccelerationZ());

  //temperature
  Serial.print("temp:");
  Serial.println(LIS.getTemperature());
  delay(500);
}
