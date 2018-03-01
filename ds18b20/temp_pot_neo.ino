#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>
#define PIN 0
#define NUM_LEDS 43
#define ONE_WIRE_BUS 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int analogInPin = A0;
int potValue = 0;
int mapPot = 0;

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
//  Serial.begin(9600);

}

void loop() {
//  strip.setBrightness(10);
  potValue = analogRead(analogInPin);
  mapPot = map(potValue, 0, 1023, 10, 30);
  
  sensors.requestTemperatures();
  int temp = sensors.getTempCByIndex(0);
//  Serial.println(mapPot);
/*  if (mapPot = temp ) {
    meteorRain(0,0,255,2, 128, true, 30);
  } */
  if (mapPot == temp ) {
    meteorRain(0, 0, 255,2, 128, true, 30);
  }

  if (temp > mapPot ) {
    meteorRain(255, 0, 0,2, 128, true, 30);
  }

  if (temp < mapPot ) {
    meteorRain(0, 255, 0,2, 128, true, 30);
  }

/*  if ( temp < 35 ) {
    meteorRain(0,255,0,2, 128, true, 30);
    delay(500);
    
  }

    if ( temp >= 35 ) {
    meteorRain(255,0,0,2, 128, true, 30);
    delay(500);
    
  } */
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
