/*
 * Jacopo Mazzoni - Firmware for RTI Controller 
 * Encoders - LCD Display - WRGB LED strip - SSRelays - color control
 */
#include <Wire.h> 
#include "src/NLC/LiquidCrystal_I2C.h"

#include "FastLED.h"
#include "FastLED_RGBW.h"

#include "Encoder.h"

// LED Params
#define NUM_LEDS 60
#define DATA_PIN 9

// Encoder 1 input pins 
#define E1_CLK 6
#define E1_DT 5
#define E1_SW 4

// Encoder 2 input pins 
#define E2_CLK 3
#define E2_DT 2
#define E2_SW 1

// Start-Stop button
#define START 7

// Relay Pin 
#define RELAY 8

// Global Encoder objects
Encoder encoder_1(E1_CLK,E1_DT,10);
Encoder encoder_2(E2_CLK,E2_DT,10);

// LCD Object
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd(0x27);

//Fastled stuff
CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];
int pivot = 0;
const uint8_t brightness = 128;

// Global variables
int photoDelay,photoDuration;
int stage;

void setup() {
  // start from the instructions phase
  stage = 0;
  
  // set io pins
  pinMode(START,INPUT);  
  pinMode(RELAY,OUTPUT);
  
  //initialize lcd
  lcd.begin(20,4);

  // Fastled init
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS));
  FastLED.setBrightness(brightness);
  FastLED.show();

}

void loop() {

  // Display instructions
  if ( stage == 0 ) {
    //TOOD: print some simple instructions on display
    lcd.setCursor(3,0);
    lcd.print("Hello World!");
    delay(3000);
    stage++;
  }
  
  // set timer options
  if ( stage == 1 ) {  
    photoDelay = encoder_1.getValue();
    photoDuration = encoder_2.getValue();
    //TODO: Convert from millis 
    //TODO: Show Vars On Diplay
    
    if ( digitalRead(START) == HIGH ){
      stage++;
    }
  }
  
  // start Photographing
  if ( stage == 2 ) {
    for(int i = 0; i < NUM_LEDS; i++){
      leds[i] = CRGBW(0, 0, 0, 0);
    }
    leds[pivot] = CRGBW(0, 0, 0, 255);
    
    FastLED.show();
    delay(50);
  
    // TODO: loop leds
    // control color
    // take picture for photoDurations millis
    // wait photoDelay millis
    // check button state ( reset to stage 1 )  
    // increment counter 
  }
}
