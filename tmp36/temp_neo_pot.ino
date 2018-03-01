/* TMP36 Pin Variables
the analog pin the TMP36's Vout (sense) pin is connected to
the resolution is 10 mV / degree centigrade with a
500 mV offset to allow for negative temperatures */

#include <Adafruit_NeoPixel.h>
#define PIN 0
#define NUM_LEDS 24

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

const int potInPin = A0;
const int tempInPin = A5;
int potValue = 0;
int mapPot = 0;
int temp = 0;

void setup() {
  strip.begin();
  strip.show();

}

void loop() {

  int potValue = analogRead(potInPin);
  int tempReading = analogRead(tempInPin);
  float voltage = tempReading * 5.0; // converting that reading to voltage, for 3.3v arduino use 3.3
  voltage /= 1024.0;
  float tempC = (voltage - 0.5) * 100 ; //converting from 10 mv per degree wit 500 mV offset to degrees ((voltage - 500mV) times 100)
  int temp = tempC;

  mapPot = map(potValue, 0, 1023, 10, 30);

  if (mapPot == temp ) {
    meteorRain(0, 0, 255,2, 128, true, 30);
  }

  if (temp > mapPot ) {
    meteorRain(255, 0, 0,2, 128, true, 30);
  }

  if (temp < mapPot ) {
    meteorRain(0, 255, 0,2, 128, true, 30);
  }

}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);
  
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    showStrip();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
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
