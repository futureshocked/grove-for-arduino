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

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain.

// This example was modified for simplicity by Peter Dalmaris so that
// it works with the DHT11 of the Grove Beginner Kit For Arduino

#include "DHT.h"

#define DHTPIN 3     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  Wire.begin();
  dht.begin();
}

void loop()
{
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C, ");
  Serial.print(dht.convertCtoF(temperature));  // See library source code: https://github.com/adafruit/DHT-sensor-library/blob/master/DHT.h
  Serial.println(" *F");

  delay(2500);
}
