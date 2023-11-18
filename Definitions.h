#include <Wire.h>
// Libraries for attached Peripheries
#include "src/NLC/LiquidCrystal_I2C.h"
#include "src/A/Adafruit_TCS34725.h"

// LED library withcustom RGBW modification
#include "src/FL/FastLED.h"
#include "FastLED_RGBW.h"

// Custom built libraries by yours truly
#include "src/E/Encoder.h"
#include "src/P/PhotoTimer.h"
#include "src/T/TimeDiff.h"

// LED Parameters
#define NUM_LEDS 144
#define DATA_PIN 7

// Encoder 1 input pins
#define E1_CLK 3
#define E1_DT 4
#define E1_SW 5

// Encoder 2 input pins
#define E2_CLK 8
#define E2_DT 9
#define E2_SW 10

#define TIMER_STEP 100

// Start-Stop button pin
#define START 12

// Relay Pin
#define RELAY 6

#define BUZZER_PIN 2
