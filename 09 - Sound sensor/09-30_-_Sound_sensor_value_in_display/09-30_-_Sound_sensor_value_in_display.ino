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

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);

const int pinAdc = A2;

int x[]        = { 0,20,30,40,50,60,70,80,90,100,128 };
int y_low[]    = { 30,30,20,40,20,40,20,40,20,30,30  };
int y_medium[] = { 30,30,20,50,20,50,20,50,20,30,30  };
int y_high[]   = { 30,30,10,60,10,60,10,60,10,30,30  };

void setup()
{
    Serial.begin(9600);
    u8g2.begin();
}

void loop()
{
    long sum = 0;
    for(int i=0; i<32; i++)
    {
        sum += analogRead(pinAdc);
    }

    sum >>= 5;
    show_sound(sum);
    Serial.println(sum); // Instead of the serial monitor, open up the serial plotter.
                          // The plotter will show the sum value as a line plot.
                          // The line will spike when a loud sound is detected by the
                          // mic. Note the range of values when there is no ambient
                          // noise. Anything above that is a loud sound.
    delay(10);
}

void show_sound(long sound_volume)
{
  u8g2_uint_t x_position = 80;
  u8g2_uint_t y_position = 60;
  int font_height = 18;

  char buffer_sound[10];
  dtostrf(sound_volume, 3, 0, buffer_sound);
  u8g2.firstPage();           // Using the firstPage / nextPage method.
                              // Advantage: much faster then the partial redraw method.
                              // Dissadvantage: must reset the whole screen every time.
  do {
      u8g2.setFont(u8g2_font_logisoso18_tf);
      u8g2.setDrawColor(1);

      // Print temperature value
      u8g2.drawStr(x_position, y_position, buffer_sound);
      // Display a visual "representation" of the sound loudness.
      for (int point=0;point<sizeof(x)/2-1;point++)
      {
        if (sound_volume < 230)
          u8g2.drawLine(  x[point], y_low[point],x[point+1], y_low[point+1]);
        else if (sound_volume < 300)
          u8g2.drawLine(  x[point],y_medium[point],x[point+1],y_medium[point+1]);
        else
          u8g2.drawLine(  x[point],y_high[point],x[point+1],y_high[point+1]);
      }

      // Print a text label
      u8g2.setFont(u8g2_font_tenthinnerguys_t_all);
      u8g2.drawStr(0, 60,  "Volume");

  } while ( u8g2.nextPage() );

}
