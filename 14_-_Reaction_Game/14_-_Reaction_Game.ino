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

#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

const byte buttonPin = 6; //2; //6; //the button or touch pin to roll the dice
const byte ledPin = 4;

long randomTimer;
int time1, time2, time3, temp, finalTime;
unsigned long startFirst, endFirst, startSecond, endSecond, startThird, endThird;

const int suspence_notes[] = {
  311, 370, 415, 466, 554, 622, 740, 831
};

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  randomSeed(analogRead(1)); // A1 is not connected to anything so it is a good source of randomness.

  u8g2.begin();

  u8g2.setDisplayRotation(U8G2_R2);

  welcome();

}

void loop() {
  // put your main code here, to run repeatedly:
  instructions();
  press_button_to_continue();
  first_try();
  second_try();
  third_try();
  scoring();
  next_player();
}

void welcome()
{
  u8g2.firstPage();           // Using the firstPage / nextPage method.
  do {
    u8g2.setFont(u8g2_font_logisoso24_tf);
    u8g2.drawStr(5, 35, "Welcome");
  } while ( u8g2.nextPage() );
  tone(5, suspence_notes[0], 500);
  delay(500);

  u8g2.firstPage();           // Using the firstPage / nextPage method.
  do {
    u8g2.setFont(u8g2_font_logisoso32_tf);
    u8g2.drawStr(30, 35, "to...");
  } while ( u8g2.nextPage() );
  tone(5, suspence_notes[1], 500);
  delay(500);

  u8g2.firstPage();           // Using the firstPage / nextPage method.
  do {
//    u8g2.setFont(u8g2_font_logisoso24_tf);
    u8g2.drawStr(0, 23, "Reaction Game");
    u8g2.drawStr(38, 60, "Game");
    u8g2.setFont(u8g2_font_open_iconic_app_4x_t); // char 72 is a stopwatch icon
    u8g2.setCursor(0, 64);
    u8g2.print(char(72));
  } while ( u8g2.nextPage() );
  tone(5, suspence_notes[2], 1000);
  delay(1000);
}

void instructions()
{
  u8g2.firstPage();           // Using the firstPage / nextPage method.
  do {
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.drawStr(0, 13, "Press button");
    u8g2.drawStr(0, 27, "on beep.");
    u8g2.drawStr(0, 47, "Best of 3");
    u8g2.drawStr(0, 63, "tries wins.");
  } while ( u8g2.nextPage() );

  delay(1000);

}

void press_button_to_continue()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.drawStr(0, 13, "Press button");
    u8g2.drawStr(0, 27, "to begin.");
  } while ( u8g2.nextPage() );
  while (digitalRead(buttonPin) == LOW)
  {
    ; // wait here until player presses the button
  }

}

void first_try()
{

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_fub17_tf);
    u8g2.drawStr(30, 25, "GET");
    u8g2.drawStr(15, 50, "READY!");
  } while ( u8g2.nextPage() );

  delay(1000);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_fub17_tf);
    u8g2.drawStr(15, 25, "FIRST");
    u8g2.drawStr(15, 50, "TRY...");
  } while ( u8g2.nextPage() );

  randomTimer = random(100, 6000);
  delay(randomTimer);
  digitalWrite(ledPin, HIGH);
  tone(5, suspence_notes[3]);
  startFirst = millis();

  while (millis() - startFirst < 5000 && digitalRead(buttonPin) != HIGH) {
    delay(1);
  }

  endFirst = millis() - startFirst;
  digitalWrite(ledPin, LOW);
  noTone(5);
  time1 = endFirst;

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_22_tf);
    u8g2.drawStr(0, 15, "First");
    u8g2.drawStr(0, 30, "reaction");
    u8g2.setCursor(10, 60);
    u8g2.print(time1);
    u8g2.drawStr(60, 60, "ms");
    u8g2.setFont(u8g2_font_open_iconic_app_4x_t); // char 72 is a stopwatch icon
    u8g2.setCursor(96, 40);
    u8g2.print(char(72));

  } while ( u8g2.nextPage() );

  delay(4000);

}

void second_try() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_fub17_tf);
    u8g2.drawStr(30, 25, "GET");
    u8g2.drawStr(15, 50, "READY!");
  } while ( u8g2.nextPage() );

  delay(1000);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_fub17_tf);
    u8g2.drawStr(15, 25, "SECOND");
    u8g2.drawStr(15, 50, "TRY...");
  } while ( u8g2.nextPage() );

  randomTimer = random(100, 6000);
  delay(randomTimer);
  digitalWrite(ledPin, HIGH);
  tone(5, suspence_notes[3]);
  startSecond = millis();

  while (millis() - startSecond < 5000 && digitalRead(buttonPin) != HIGH) {
    delay(1);
  }

  endSecond = millis() - startSecond;
  digitalWrite(ledPin, LOW);
  noTone(5);
  time2 = endSecond;

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_22_tf);
    u8g2.drawStr(0, 15, "Second");
    u8g2.drawStr(0, 30, "reaction");
    u8g2.setCursor(10, 60);
    u8g2.print(time2);
    u8g2.drawStr(60, 60, "ms");
    u8g2.setFont(u8g2_font_open_iconic_app_4x_t); // char 72 is a stopwatch icon
    u8g2.setCursor(96, 40);
    u8g2.print(char(72));

  } while ( u8g2.nextPage() );

  delay(4000);
}

void third_try() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_fub17_tf);
    u8g2.drawStr(30, 25, "GET");
    u8g2.drawStr(15, 50, "READY!");
  } while ( u8g2.nextPage() );

  delay(1000);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_fub17_tf);
    u8g2.drawStr(15, 25, "THIRD");
    u8g2.drawStr(15, 50, "TRY...");
  } while ( u8g2.nextPage() );

  randomTimer = random(100, 6000);
  delay(randomTimer);
  digitalWrite(ledPin, HIGH);
  tone(5, suspence_notes[3]);
  startThird = millis();

  while (millis() - startThird < 5000 && digitalRead(buttonPin) != HIGH) {
    delay(1);
  }

  endThird = millis() - startThird;
  digitalWrite(ledPin, LOW);
  noTone(5);
  time3 = endThird;

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_22_tf);
    u8g2.drawStr(0, 15, "Third");
    u8g2.drawStr(0, 30, "reaction");
    u8g2.setCursor(10, 60);
    u8g2.print(time3);
    u8g2.drawStr(60, 60, "ms");
    u8g2.setFont(u8g2_font_open_iconic_app_4x_t); // char 72 is a stopwatch icon
    u8g2.setCursor(96, 40);
    u8g2.print(char(72));

  } while ( u8g2.nextPage() );

  delay(4000);
}

void scoring()
{
  if (time1 > time2) {
    temp = time2;
  } else if (time1 < time2) {
    temp = time1;
  }
  if (temp > time3) {
    finalTime = time3;
  } else if (temp < time3) {
    finalTime = temp;
  }

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_22_tf);
    u8g2.drawStr(0, 15, "Best");
    u8g2.drawStr(0, 30, "reaction");
    u8g2.setCursor(10, 60);
    u8g2.print(finalTime);
    u8g2.drawStr(60, 60, "ms");
    u8g2.setFont(u8g2_font_open_iconic_app_4x_t); // char 72 is a stopwatch icon
    u8g2.setCursor(96, 40);
    u8g2.print(char(72));

  } while ( u8g2.nextPage() );
  delay(4000);


}

void next_player()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_22_tf);
    u8g2.drawStr(0, 15, "Well");
    u8g2.drawStr(0, 30, "Done!");
    u8g2.setFont(u8g2_font_open_iconic_app_4x_t); // char 72 is a stopwatch icon
    u8g2.setCursor(96, 40);
    u8g2.print(char(72));

  } while ( u8g2.nextPage() );

  delay(3000);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_22_tf);
    u8g2.drawStr(0, 15, "Next");
    u8g2.drawStr(0, 30, "Player!");
    u8g2.setFont(u8g2_font_open_iconic_app_4x_t); // char 72 is a stopwatch icon
    u8g2.setCursor(96, 40);
    u8g2.print(char(72));

  } while ( u8g2.nextPage() );

  delay(4500);
}
