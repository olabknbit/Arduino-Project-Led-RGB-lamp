#include <LEDS.h>
#include <OneWire.h>
#include <DS18B20.h>

/* Here specify the number of leds and theirs Digital Pin as well as OneWire pin */
#define LED_PIN 6
#define ONEWIRE_PIN 2
#define LED_COUNT 2

LedStrip<LED_PIN> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[LED_COUNT];

// One wire address
byte one_wire_address[8] = {0x28, 0xFF, 0x19, 0xB, 0x64, 0x16, 0x4, 0x4F};

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);

unsigned char r = 0;
unsigned char g = 50;
unsigned char b = 80;

void setup()
{
  Serial.begin(9600);

  sensors.begin();
  sensors.request(address);
}


void showColors()
{  
  colors[0] = (rgb_color){r, g, b};
  colors[1] = (rgb_color){(r + 50) % 255, (g + 50) % 255, (b + 50) % 255};
  r = (r + 10)%255;
  g = (g + 10)%255;
  b = (b + 10)%255;
}

// Shows temperature on two leds :
// First led represents the first digit: it can become one of 7 values from indigo dye to red.
// Second led can take all values between (0,0,255) to (255,0,0) with (255,255,255) in the middle.
// This, in our opinion, represents the most intuitially the tempreture on two leds.
void displayTemperatureOnTwoLeds(float temp) {
  int temp1 = (int) (temp / 10);
  int temp2 = ((int) temp) % 10;
  int temp3 = (int) ((temp - (10 * temp1) - temp2) * 100);
  rgb_color indigo_dye = {9, 31, 146};
  rgb_color royal_blue = {65,105,225};
  rgb_color powder_blue = {176,224,230};
  rgb_color white = {255, 255, 255};
  rgb_color golden_yellow = {255,223,0};
  rgb_color dark_orange = {255,140,0};
  rgb_color red = {255, 0, 0};
  
  if (temp1 <= -2) {
    colors[0] = indigo_dye;
  } else if (temp1 <= -1) {
    colors[0] = royal_blue;
  } else if (temp1 <= 0) {
    colors[0] = powder_blue;
  } else if (temp1 <= 1) {
    colors[0] = white;
  } else if (temp1 <=2) {
    colors[0] = golden_yellow;
  } else if (temp1 <= 3) {
    colors[0] = dark_orange;
  } else {
    colors[0] = red;
  }
  
  if (temp2 > 5) {
    r = 255;
    g = b = 255 - (51 * temp2 + (temp3/2));
  } else if (temp2 == 5) {
    r = g = b = 255;
  } else {
    b = 255;
    r = g = 51 * temp2 + (temp3/2);
  }
  colors[1] = (rgb_color) {r, g, b};
}

void showNothing()
{
  r = g = b = 0;
  colors[0] = (rgb_color){r, g, b};
  colors[1] = (rgb_color){r,g,b};
}

void loop()
{
  if (sensors.available())
  {
    float temperature = sensors.readTemperature(address);

    Serial.print(temperature);
    Serial.println(F(" 'C"));
    
    displayTemperatureOnTwoLeds(temperature);
    ledStrip.write(colors, LED_COUNT);
    delay(60);
    
    sensors.request(address);
  }
  
}





