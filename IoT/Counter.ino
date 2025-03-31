#include <Wire.h>
#include <RTClib.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// ===== HARDWARE SETUP =====
const int touchPins[] = {2, 3, 4, 5, 6}; // Sensors 1-5
#define TFT_CS   10
#define TFT_RST  8
#define TFT_DC   9

// ===== VARIABLES =====
int token = 0;
int currentToken = 0;
int counters[] = {0, 0, 0, 0};
bool sensorActive[] = {false, false, false, false, false};
String lastTimeStr = "";
String lastDateStr = "";
String lastTokenStr = "";
String lastCounterStrs[4] = {"", "", "", ""};

// ===== DISPLAY & RTC =====
RTC_DS3231 rtc;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Updated color scheme
const uint16_t COUNTER_COLORS[] = {
  ST7735_MAGENTA,    // Counter 1 value
  ST7735_YELLOW,     // Counter 2 value
  ST7735_ORANGE,     // Counter 3 value
  ST7735_GREEN       // Counter 4 value
};

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  for (int i = 0; i < 5; i++) {
    pinMode(touchPins[i], INPUT);
  }

  tft.initR(INITR_BLACKTAB);  
  tft.fillScreen(ST7735_BLACK);  
  tft.setTextSize(1);

  if (!rtc.begin()) {
    Serial.println("RTC ERROR");
    while (1);
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Draw static elements once
  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(35, 5);
  tft.println(" CSK BANK");
}

void loop() {
  DateTime now = rtc.now();
  static unsigned long lastDisplayUpdate = 0;

  // Touch sensor logic
  for (int i = 0; i < 5; i++) {
    bool isTouched = digitalRead(touchPins[i]);

    if (isTouched && !sensorActive[i]) {
      sensorActive[i] = true;
      
      if (i == 4) {
        token++;
        Serial.println("TOKEN +1");
      }
      else if (token > currentToken) {
        currentToken++;
        counters[i] = currentToken;
        Serial.print("COUNTER ");
        Serial.print(i + 1);
        Serial.println(" +1");
      }
      delay(200);
    }
    else if (!isTouched && sensorActive[i]) {
      sensorActive[i] = false;
    }
  }

  // Display update - only when needed
  if (millis() - lastDisplayUpdate >= 500) {
    lastDisplayUpdate = millis();
    
    String timeStr = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
    String dateStr = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
    String tokenStr = String(currentToken) + "/" + String(token);

    // Only update changed elements
    if (timeStr != lastTimeStr || dateStr != lastDateStr) {
      tft.setTextColor(ST7735_YELLOW);
      tft.setCursor(10, 30);
      tft.fillRect(10, 30, tft.width()-10, 20, ST7735_BLACK); // Clear only time/date area
      tft.print(dateStr);
      tft.setCursor(10, 40);
      tft.print(timeStr);
      lastTimeStr = timeStr;
      lastDateStr = dateStr;
    }

    if (tokenStr != lastTokenStr) {
      tft.setTextColor(ST7735_RED);
      tft.setCursor(10, 60);
      tft.fillRect(10, 60, tft.width()-10, 10, ST7735_BLACK); // Clear only token area
      tft.print("TOKENS: ");
      tft.setTextColor(ST7735_CYAN);
      tft.print(tokenStr);
      lastTokenStr = tokenStr;
    }

    // Update counters only if changed
    for (int i = 0; i < 4; i++) {
      String currentCounterStr = String(counters[i]);
      if (currentCounterStr != lastCounterStrs[i]) {
        tft.setCursor(10, 80 + i * 15);
        tft.fillRect(10, 80 + i * 15, tft.width()-10, 10, ST7735_BLACK); // Clear only this counter line
        tft.setTextColor(ST7735_WHITE);
        tft.print("Counter ");
        tft.print(i + 1);
        tft.print(": ");
        tft.setTextColor(COUNTER_COLORS[i]);
        tft.print(currentCounterStr);
        lastCounterStrs[i] = currentCounterStr;
      }
    }
  }
}
