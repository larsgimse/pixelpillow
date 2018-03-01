#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>
#define PIN 0
#define NUM_LEDS 72
#define ONE_WIRE_BUS 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int red[3]    = { 255, 0, 0 };
int green[3]    = { 0, 255, 0 };
int blue[3]    = { 0, 0, 255 };
int yellow[3]    = { 255, 255, 0 };
int purple[3]    = { 80, 0, 80 };
int aqua[3]    = { 0, 255, 255 };
int off[3]    = { 0, 0, 0 };

// int temp = sensors.getTempCByIndex(0);

void setup() {
  sensors.begin();
  strip.begin();
  strip.show();

}

void loop() {
  strip.setBrightness(10);
  sensors.requestTemperatures();
  int temp = sensors.getTempCByIndex(0);
  setAll(temp*10, 0, 0);

/*  if (temp > 25) {
    neoColor(red);
    delay(100);
  }
  
  if (temp < 25) {
    neoColor(green);
    delay(100);
  } */

}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}

void neoColor(int color[3]) {
  for( int i = 0; i<NUM_LEDS; i++){
    strip.setPixelColor(i, strip.Color(color[0], color[1], color[2]));
    strip.show();
    }
  }

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
