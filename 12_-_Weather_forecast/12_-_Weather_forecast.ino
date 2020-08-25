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

// For some background on how to use a barometer (temperature sensor) to do
// a short-term weather prediction, see https://en.wikipedia.org/wiki/Barometer#Applications
// And https://www.thoughtco.com/how-to-read-a-barometer-3444043

#include "Seeed_BMP280.h"
#include <Wire.h>

#include "DHT.h"

#include <U8g2lib.h>  // Install the U8g2 by searching it by name in the Library Manager.
// Documentation: https://github.com/olikraus/u8g2/wiki/u8g2reference

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);

#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BMP280 bmp280;

float temp = 0, pres = 0; // Will get these values from the BMP280

int humid = 0; // Will get this value from the DHT11

float pressure[60];   //array of pressure readings

int measurement = 1;
int seconds_since_last_evaluation = 0;
char prediction[20] = "Getting data.";

void setup() {
  Serial.begin(9600);
  u8g2.begin();

  if (!bmp280.init()) {
    Serial.println("Device error!");
  }
}

void loop() {
  get_readings();
  print_sensor_readings();
  calculate_forecast();
  delay(1000); // refresh display every 1 seconds.
  seconds_since_last_evaluation += 1;
  Serial.println(seconds_since_last_evaluation);
}

void get_readings()
{
  temp = bmp280.getTemperature();
  pres = bmp280.getPressure();
  humid = dht.readHumidity();
}

void print_sensor_readings()
{
  int font_height = 14;

  u8g2_uint_t x_position_temp = 0;
  u8g2_uint_t y_position_temp = 14;

  u8g2_uint_t x_position_pres = 0;
  u8g2_uint_t y_position_pres = 46;

  u8g2_uint_t x_position_hum = 0;
  u8g2_uint_t y_position_hum = 30;

  char buffer_pres[10];
  dtostrf(pres, 4, 2, buffer_pres);

  char buffer_temp[10];
  dtostrf(temp, 4, 2, buffer_temp);

  char buffer_hum[10];
  dtostrf(humid, 4, 2, buffer_hum);

  u8g2.firstPage();           // Using the firstPage / nextPage method.

  do {
    u8g2.setFont(u8g2_font_crox4hb_tf); // This is a 14-point font
    u8g2.setDrawColor(1);

    // Print temperature value
    u8g2.drawHLine(x_position_temp + 58, y_position_temp - 1, 32);
    u8g2.drawStr(x_position_temp, y_position_temp, buffer_temp);
    u8g2.setCursor(x_position_temp + 95, y_position_temp);
    u8g2.print(char(0xB0));   // This or one of the next two lines can print the degrees symbol
    u8g2.print("C");

    // Print pressure value
    u8g2.drawStr(x_position_pres, y_position_pres, buffer_pres);
    u8g2.setCursor(x_position_pres + 95, y_position_pres);
    u8g2.print("Pa");

    // Print humidity value
    u8g2.drawHLine(x_position_hum + 58, y_position_hum - 1, 32);
    u8g2.drawStr(x_position_hum, y_position_hum, buffer_hum);
    u8g2.setCursor(x_position_hum + 95, y_position_hum);
    u8g2.print("%");

    u8g2.setFont(u8g2_font_tenthinnerguys_t_all);
    u8g2.drawStr(0, 60,  prediction);

  } while ( u8g2.nextPage() );
}

void calculate_forecast()
{
  float pressureDifference;
  float percentageChange;


  // No need to evaluate too often.
  // Once per minute is enough.
  if (seconds_since_last_evaluation == 60)
  {
    pressure[measurement - 1] = pres;
    pressureDifference = abs(pressure[measurement - 1] - pressure[0]);
    percentageChange = (pressureDifference / pressure[0]) * 100;

    String message = "";

    if (measurement > 2)
    {
      //Calculating the percentage change of the pressure readings
      //Compare the latest pressure measurements against the first one.
      if (percentageChange > 5 && pressure[measurement - 1] > pressure[0]) {
        // Rising pressure suggests improving weather
        message += "Improving";
      } else if (percentageChange > 5 && pressure[measurement - 1] < pressure[0]) {
        // Dropping pressure suggests worsening weather
        message += "Worsening";
      } else {
        message += "No change";
      }
      message += " diff ";
      message += String(pressureDifference, 0);
    }
    else
    {
      message += "Getting data.";
    }

    message.toCharArray(prediction, 18);
    measurement = measurement + 1;

    if (measurement == 61)
      measurement = 1;

    seconds_since_last_evaluation = 0;
  }
}
