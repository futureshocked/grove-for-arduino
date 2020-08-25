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

// This sketch contains code from section 3 (how to use the buzzer), 4 and 5 (how to use the OLED).

#include <U8g2lib.h>
#include <Wire.h>
#include "pitches.h"

// See documentation for u8g2: https://github.com/olikraus/u8g2/wiki/u8g2reference

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

int button = 6; //the button pin to roll the dice
int state = 0;  //button initial state
long randomNumber;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int suspence_notes[] = {
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_AS4, NOTE_CS5, NOTE_DS5, NOTE_FS5, NOTE_GS5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup(void) {
  Serial.begin(9600);
  randomSeed(analogRead(1)); // A1 is not connected to anything so it is a good source of randomness.

  u8g2.begin();

  u8g2.setDisplayRotation(U8G2_R2);

  randomNumber = random(1, 7);
  dicing(5);
  drawDice();
  display_lucky_number(randomNumber);
}

void loop(void) {
  if (digitalRead(button) == HIGH && state == 0)    //read the button state; if high then roll the dice
  {
    state = 1;
    Serial.print(state);
    for (int i = 0; i < 6; i++)
    {
      randomNumber = random(1, 7);
      Serial.print(", ");
      Serial.print(randomNumber);
      u8g2.firstPage();           // Using the firstPage / nextPage method.
      do {
        dicing(i);
        play_suspence_tone(i);
        drawDice();
        display_lucky_number(randomNumber);
      } while ( u8g2.nextPage() );
    }
    state = 0;
    Serial.print(", ");
    Serial.println(state);
    play_music();
  }
  else
  {
    display_lucky_number(randomNumber);
    u8g2.setFont(u8g2_font_ncenB08_tr);   // Fonts reference: https://github.com/olikraus/u8g2/wiki/fntlistall#15-pixel-height
    u8g2.drawStr(61, 64, "Press button");
    u8g2.sendBuffer();
  }
}

void display_lucky_number(int lucky_number)
{
  switch (lucky_number) {
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    default:
      one();
      break;
  }
}

void dicing(int draw) {
  u8g2.setFont(u8g2_font_ncenB08_tr);   // choose a suitable font
  if (draw < 5)
    u8g2.drawStr(68, 15, "Drawing");
  else if (draw == 5)
    u8g2.drawStr(75, 15, "Ready");
  else
    u8g2.drawStr(68, 15, "Dice Draw");
}

void drawDice()
{
  // The frame has a two-pixel width by frawing two frames.
  u8g2.drawRFrame(6, 6, 52, 52, 5);
  u8g2.drawRFrame(5, 5, 54, 54, 5);
}

void one()
{
  u8g2.drawDisc(32, 32, 5, U8G2_DRAW_ALL);

  u8g2.setFont(u8g2_font_logisoso28_tf);   // Fonts reference: https://github.com/olikraus/u8g2/wiki/fntlistall#15-pixel-height
  u8g2.drawStr(90, 52, "1");
}

void two()
{
  u8g2.drawDisc(16, 16, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(48, 48, 5, U8G2_DRAW_ALL);

  u8g2.setFont(u8g2_font_logisoso28_tf);   // Fonts reference: https://github.com/olikraus/u8g2/wiki/fntlistall#15-pixel-height
  u8g2.drawStr(90, 52, "2");
}

void three()
{
  u8g2.drawDisc(16, 48, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(32, 32, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(48, 16, 5, U8G2_DRAW_ALL);

  u8g2.setFont(u8g2_font_logisoso28_tf);   // Fonts reference: https://github.com/olikraus/u8g2/wiki/fntlistall#15-pixel-height
  u8g2.drawStr(90, 52, "3");
}

void four()
{
  u8g2.drawDisc(16, 16, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(48, 16, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(16, 48, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(48, 48, 5, U8G2_DRAW_ALL);

  u8g2.setFont(u8g2_font_logisoso28_tf);   // Fonts reference: https://github.com/olikraus/u8g2/wiki/fntlistall#15-pixel-height
  u8g2.drawStr(90, 52, "4");
}

void five()
{
  u8g2.drawDisc(16, 16, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(48, 16, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(16, 48, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(48, 48, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(32, 32, 5, U8G2_DRAW_ALL);

  u8g2.setFont(u8g2_font_logisoso28_tf);   // Fonts reference: https://github.com/olikraus/u8g2/wiki/fntlistall#15-pixel-height
  u8g2.drawStr(90, 52, "5");
}

void six()
{
  u8g2.drawDisc(16, 16, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(32, 16, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(48, 16, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(16, 48, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(32, 48, 5, U8G2_DRAW_ALL);
  u8g2.drawDisc(48, 48, 5, U8G2_DRAW_ALL);

  u8g2.setFont(u8g2_font_logisoso28_tf);   // Fonts reference: https://github.com/olikraus/u8g2/wiki/fntlistall#15-pixel-height
  u8g2.drawStr(90, 52, "6");
}

void play_music()
{
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(5, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(5);
  }
}

void play_suspence_tone(int tone_number)
{
  tone(5, suspence_notes[tone_number], 3000);
}
