#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <EEPROM.h>

// Pin Definitions
#define RELAY_PIN_COUNT 6
const int relayPins[RELAY_PIN_COUNT] = {17, 18, 19, 20, 21, 22};

#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

// MCUFRIEND TFT Display and TouchScreen Declarations  
MCUFRIEND_kbv myGLCD;
TouchScreen ts = TouchScreen(XP, A3, A2, YM, 300);

// Constants
const float TIME_BY_ML = 740; // Time for delivery of 1mL

char* drinksName[RELAY_PIN_COUNT] = {
  "Vodka",        // Baza dla wielu koktajli
  "Gin",          // Kolejna wszechstronna baza
  "Rum",          // Do drinków tropikalnych i klasycznych
  "Triple Sec",   // Likier o smaku pomarańczowym
  "Orange Juice", // Sok pomarańczowy, popularny mixer
  "Sprite"        // Popularny napój gazowany
};

char* cocktailsName[] = {
  "Screwdriver",          // Wódka i sok pomarańczowy
  "Gin Fizz",             // Gin i Sprite
  "Cuba Libre",           // Rum i Sprite
  "Orange Blossom",       // Gin i sok pomarańczowy
  "Vodka Sunrise",        // Wódka, sok pomarańczowy i Triple Sec
  "Rum Punch",            // Rum, sok pomarańczowy i Triple Sec
  "Gin and Juice",        // Gin i sok pomarańczowy
  "Tropical Splash",      // Rum, sok pomarańczowy i Sprite
  "Orange Vodka",         // Wódka i sok pomarańczowy
  "Orange Gin",           // Gin i sok pomarańczowy
  "Citrus Burst",         // Wódka, Triple Sec i sok pomarańczowy
  "Rum Cooler",           // Rum, Sprite i sok pomarańczowy
  "Vodka Spritzer",       // Wódka i Sprite
  "Gin Spritzer",         // Gin i Sprite
  "Sunset Cocktail",      // Rum, Triple Sec, sok pomarańczowy i Sprite
  "Vodka Delight",        // Wódka, Sprite i sok pomarańczowy
  "Orange Crush",         // Triple Sec, sok pomarańczowy i Sprite
  "Citrus Rum",           // Rum, sok pomarańczowy i Sprite
  "Gin Cooler",           // Gin, sok pomarańczowy i Triple Sec
  "Triple Sunset",        // Rum, wódka, sok pomarańczowy i Triple Sec
  "Sprite Breeze",        // Wódka, rum i Sprite
  "Orange Rum",           // Rum, sok pomarańczowy i Triple Sec
  "Citrus Vodka",         // Wódka, Triple Sec i Sprite
  "Tropical Fizz",        // Rum, Sprite i Triple Sec
  "Summer Splash",        // Wódka, sok pomarańczowy i Sprite
  "Sunshine Cooler",      // Gin, sok pomarańczowy i Sprite
  "Rum & Orange",         // Rum i sok pomarańczowy
  "Citrus Spritz",        // Wódka, gin, sok pomarańczowy i Sprite
  "Island Breeze",        // Rum, Triple Sec, sok pomarańczowy i Sprite
  "Orange Twist",         // Wódka, gin, sok pomarańczowy i Triple Sec
};

char* funnySentence[] = {
  "Step Aside COFFEE This is a Job for ALCOHOL",
  "If life gives you lemons, Add VODKA",
  "Alcohol You Later",
  "'Drunkenness is nothing but voluntary madness.'  - Seneca",
  "Not to get technical, But according to chemistry ALCOHOL is a solution",
  "You say alcoholism, I say liver crossfit",
  "To me 'Drink responsibly' means dont spill it"
};

const int FUNNY_SENTENCE_SIZE = sizeof(funnySentence) / sizeof(char *);
const int SIZE_OF_COCKTAILS = sizeof(cocktailsName) / sizeof(char *);

int drinksComposition[SIZE_OF_COCKTAILS][RELAY_PIN_COUNT] = {
  {40, 0, 0, 0, 100, 0}, // Screwdriver
  {0, 40, 0, 0, 0, 100}, // Gin Fizz
  {0, 0, 40, 0, 0, 100}, // Cuba Libre
  {0, 40, 0, 0, 100, 0}, // Orange Blossom
  {40, 0, 0, 20, 100, 0}, // Vodka Sunrise
  {0, 0, 40, 20, 100, 0}, // Rum Punch
  {0, 40, 0, 0, 100, 0}, // Gin and Juice
  {0, 0, 40, 0, 60, 40}, // Tropical Splash
  {40, 0, 0, 0, 100, 0}, // Orange Vodka
  {0, 40, 0, 0, 100, 0}, // Orange Gin
  {40, 0, 0, 20, 100, 0}, // Citrus Burst
  {0, 0, 40, 0, 60, 40}, // Rum Cooler
  {40, 0, 0, 0, 0, 100}, // Vodka Spritzer
  {0, 40, 0, 0, 0, 100}, // Gin Spritzer
  {0, 0, 40, 20, 60, 40}, // Sunset Cocktail
  {40, 0, 0, 0, 60, 40}, // Vodka Delight
  {0, 0, 0, 40, 100, 40}, // Orange Crush
  {0, 0, 40, 0, 60, 40}, // Citrus Rum
  {0, 40, 0, 20, 60, 40}, // Gin Cooler
  {20, 0, 20, 20, 60, 40}, // Triple Sunset
  {20, 0, 20, 0, 0, 60}, // Sprite Breeze
  {0, 0, 40, 20, 60, 0}, // Orange Rum
  {20, 0, 0, 40, 0, 60}, // Citrus Vodka
  {0, 0, 40, 20, 0, 60}, // Tropical Fizz
  {20, 0, 0, 20, 60, 40}, // Summer Splash
  {0, 40, 0, 20, 60, 40}, // Sunshine Cooler
  {0, 0, 40, 0, 100, 0}, // Rum & Orange
  {20, 20, 0, 20, 60, 40}, // Citrus Spritz
  {0, 0, 20, 40, 60, 40}, // Island Breeze
  {20, 20, 0, 20, 60, 0}, // Orange Twist
};

// Calibration parameters for 800x480 display
#define TS_MINX 150
#define TS_MAXX 920
#define TS_MINY 120
#define TS_MAXY 940

// Function Declarations
void waitForTouch();
void motor(int cocktailValue);
void drink(int currentPage);
void drinkConfirmation(int cocktailValue);
int positionTouch(int x1Button, int y1Button, int x2Button, int y2Button, TSPoint p);
void drawTopText(char* text);
void drawBottomText(char* text);
void param();
void splashScreen();
void cleanSystem();  // New cleaning function

bool splashScreenFinished = false;

void setup() {
  Serial.begin(9600);
  
  // Initialize relay pins
  for (int i = 0; i < RELAY_PIN_COUNT; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }

  // Initialize MCUFRIEND TFT 800x480 LCD
  uint16_t ID = myGLCD.readID();
  myGLCD.begin(ID);
  myGLCD.setRotation(1);  // Landscape orientation
  myGLCD.fillScreen(TFT_BLACK);  // Clear screen with black

  // Display splash screen
  splashScreen();
}

void loop() {
  if (splashScreenFinished) {
    drink(0);
  } else {
    delay(100); // Small delay to avoid rapid checking
  }
}
