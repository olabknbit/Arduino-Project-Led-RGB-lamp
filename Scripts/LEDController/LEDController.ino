#include <LEDS.h>

/* Here specify the number of leds and Digital Pin */
#define D_PIN 6
#define LED_COUNT 2
LedStrip<D_PIN> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[LED_COUNT];

unsigned char r = 0;
unsigned char g = 50;
unsigned char b = 80;

void setup()
{

}


void showColors(int temp)
{  
  colors[0] = (rgb_color){r, g, b};
  colors[1] = (rgb_color){(r + 50) % 255, (g + 50) % 255, (b + 50) % 255};
  r = (r + 10)%255;
  g = (g + 10)%255;
  b = (b + 10)%255;
  ledStrip.write(colors, LED_COUNT);
}

void showNothing()
{
  r = g = b = 0;
  colors[0] = (rgb_color){r, g, b};
  colors[1] = (rgb_color){r,g,b};
  ledStrip.write(colors, LED_COUNT);
}

void loop()
{
  
  //showColors();
  showNothing();
  delay(1000);
}




