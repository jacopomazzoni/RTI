/*
   Jacopo Mazzoni - Firmware for RTI Controller
   Encoders - LCD Display - WRGB LED strip - Relay - color control
*/
// all includes and constants defined here
#include "Definitions.h"

// Global PhotoTimer Object
PhotoTimer shutterSpeed;

// Global Encoder objects
Encoder encoder_1(E1_CLK, E1_DT, TIMER_STEP, 1, 90000);
Encoder encoder_2(E2_CLK, E2_DT, 1);

// LCD Object
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// String to manipulate for padded output on LCD
char lineBuffer [20];

// Color Sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


//Fastled Objects and structs
CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];

//active led index
int pivot = 0;
// easily tweakable brightness value
const uint8_t brightness = 128;

// Global variables to improve encoder input
int photoDelay, photoDuration;
int prevDelay, prevDuration;

// indicates what menu-scanning phase we are in
int stage;

//encoder switches management variables
int sw1_v, sw1_p;
int sw2_v, sw2_p;

//color sensor output variables
float red, green, blue;

// how long to display instruction message at the beginning
int countdown = 1;

//calculate time passed between two milliseconds

TimeDiff t1;
TimeDiff t2;

float ETA;

void printInfo(PhotoTimer, int);
float calcETA(int, int);
void turnoffLED(CRGBW *leds, int n);

void setup() {
  // start from the instructions phase
  stage = 0;

  // set io pins
  pinMode(START, INPUT_PULLUP);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  pinMode(BUZZER_PIN, OUTPUT);
  
  //initialize lcd
  lcd.begin(20, 4);

  // Fastled init
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS));
  FastLED.setBrightness(brightness);
  FastLED.show();

  prevDelay = encoder_1.getValue();
  prevDuration = encoder_2.getValue();
  pinMode (E1_SW, INPUT_PULLUP);
  pinMode (E2_SW, INPUT_PULLUP);
  sw1_p = digitalRead(E1_SW);
  sw2_p = digitalRead(E2_SW);
  if (tcs.begin()) {
    tcs.setInterrupt(true);  // turn off LED
  }
}


void loop() {

  // Display instructions ===========================
  if ( stage == 0 ) {
    lcd.setCursor(0, 0);
    lcd.print("RTI Dome Controller");
    lcd.setCursor(10, 1);
    lcd.print(countdown);
    lcd.setCursor(0, 2);
    lcd.print("START ->  RED Btn");
    lcd.setCursor(0, 3);
    lcd.print("OFF   -> 2xON Btn");

    delay(1000);
    countdown--;
    lcd.clear();
    if ( countdown <= 0 ) {
      stage++;
      printInfo( shutterSpeed, photoDelay);
    }
  }

  // set timer options ===========================================================================
  if ( stage == 1 ) {

    photoDelay = abs(encoder_1.getValue());
    photoDuration = abs(encoder_2.getValue());

    shutterSpeed.goTo(photoDuration);

    if (photoDelay != prevDelay || photoDuration != prevDuration ) {
      printInfo( shutterSpeed, photoDelay);
      //Serial.print(photoDelay);
      //Serial.print(" - ");
      //Serial.println(encoder_1.getValue());
    }

    prevDelay = photoDelay;
    prevDuration = photoDuration;

    // advance to next stage condition
    if ( digitalRead(START) == LOW ) { 
      stage++;
      lcd.clear();
      t1.setStart();
      t2.setStart();
      t2.setStop(ETA+millis());
      pivot = 0;
    }
  }
  
  // start Photographing ===================================================
  if ( stage == 2 ) {
    
    // if button is still down continue taking pictures 
    if ( digitalRead(START) == LOW ) {
      // update timer to know how much time has passed
      t1.setStop();
      
      // get baseline color info
      tcs.getRGB(&red, &green, &blue);

      // display info
      lcd.clear();
      // led percentage progress
      lcd.setCursor(0, 0);
      //lcd.print("Scan progress: %d%");
      //lcd.setCursor(0, 3);
      sprintf(lineBuffer, "Scan Progress: %d%%", 100 * pivot / NUM_LEDS);
      lcd.print(lineBuffer);

      // led progress
      lcd.setCursor(0, 1);
      sprintf(lineBuffer, "LED %3d/%d", pivot, NUM_LEDS);
      lcd.print(lineBuffer);

      // time left
      lcd.setCursor(0, 2);
      t2.setStart(); // count from zero to
      //t2.setStop(ETA); // estimated time in millis
      sprintf(lineBuffer, "%02dm%02ds ETA:%02dm%02ds", t1.getMinutes(), t1.getSeconds() % 60, t2.getMinutes(), t2.getSeconds() % 60);
      lcd.print(lineBuffer);

      

      // turn all leds off
      turnoffLED(leds, NUM_LEDS);

      leds[pivot] = CRGBW(0, 0, 0, 255);
      pivot++;

      FastLED.show();
      delay(50);

      // TODO: TAKE PICTURE HERE
      digitalWrite(RELAY, LOW);
      delay(shutterSpeed.getMillis());
      digitalWrite(RELAY, HIGH);
      delay(photoDelay);

      if ( pivot == NUM_LEDS) {

        // take a green picture

        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
        delay(100);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
        delay(100);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Scan Successfull!!");
        lcd.setCursor(0, 1);
        lcd.print("Release RED button ");
        lcd.setCursor(0, 2);
        lcd.print("to go back!");
        lcd.setCursor(0, 3);
        sprintf(lineBuffer, "Scan took %02dm%02ds", t1.getMinutes(), t1.getSeconds() % 60);
        lcd.print(lineBuffer);
        // turn all leds off
        turnoffLED(leds, NUM_LEDS);
        FastLED.show();
        
        // take a red picture

        // wait for button to reset
        while (digitalRead(START) == LOW) {};
        turnoffLED(leds, NUM_LEDS);
        FastLED.show();
        lcd.clear();
        printInfo( shutterSpeed, photoDelay);
        stage--;
      }
      
    } else { // if button is released stop and go back
        turnoffLED(leds, NUM_LEDS);
        FastLED.show();
        lcd.clear();
        printInfo(shutterSpeed, photoDelay);
        // take a red picture
        stage--;

    }
  }



}

void printInfo(PhotoTimer a, int b) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set timer options");
  sprintf(lineBuffer, "1/%3ds   %4dms", a.getFraction(), b);
  lcd.setCursor(0, 1);
  lcd.print("Exp      Delay");
  lcd.setCursor(0, 2);
  lcd.print(lineBuffer);
  lcd.setCursor(0, 3);
  ETA = calcETA(a.getMillis(), b);
  t2.setStart(0);
  t2.setStop(ETA);
  sprintf(lineBuffer, "Est: %02dm%02ds", t2.getMinutes(), t2.getSeconds() % 60);
  lcd.print(lineBuffer);
}

float calcETA(int a, int b) {
  const int est_calc_time = 160;
  float x = a + b + est_calc_time;
  x *= NUM_LEDS;
  return x;
}


void turnoffLED(CRGBW *leds, int n) {
  for (int i = 0; i < n; i++) {
    leds[i] = CRGBW(0, 0, 0, 0);
  }
}
