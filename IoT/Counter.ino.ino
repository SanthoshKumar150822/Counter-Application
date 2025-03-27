#include <Wire.h>
#include <RTClib.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

int touchSensor1=2, touchSensor2=3, touchSensor3=4, touchSensor4=5, touchSensor5=6;
int token=0, currentToken=0, counter1=0, counter2=0, counter3=0, counter4=0;

#define TFT_CS   10
#define TFT_RST  9
#define TFT_DC   8

RTC_DS3231 rtc;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() 
{
    Serial.begin(9600);
    Wire.begin();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);

    tft.initR(INITR_BLACKTAB);  
    tft.fillScreen(ST7735_BLACK);  
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);  

    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting time...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set time to compile time
    }
}

void loop() 
{
    DateTime now = rtc.now();

    String dateTimeStr = String(now.year()) + "/" + 
                         String(now.month()) + "/" + 
                         String(now.day()) + "  " + 
                         String(now.hour()) + ":" + 
                         String(now.minute()) + ":" + 
                         String(now.second());

    if(touchSensor1==HIGH)
    {        
        if(token>currentToken)
        {
          currentToken++;
          counter1=currentToken;
        }
    }

    if(touchSensor2==HIGH)
    {
        if(token>currentToken)
        {
          currentToken++;
          counter1=currentToken;
        }
    }
  
    if(touchSensor3==HIGH)
    {
        if(token>currentToken)
        {
          currentToken++;
          counter1=currentToken;
        }
    }

    if(touchSensor4==HIGH)
    {
        if(token>currentToken)
        {
          currentToken++;
          counter1=currentToken;
        }
    }

    if(touchSensor5==HIGH)
    {
        token++;
    }

    // Print to Serial Monitor
    Serial.println(dateTimeStr);
    Serial.print("Counter1:"); Serial.print(counter1);     Serial.print("\t\t\t");     Serial.print("Counter2:"); Serial.println(counter2); 
    Serial.print("Counter3:"); Serial.print(counter3);     Serial.print("\t\t\t");     Serial.print("Counter4:"); Serial.println(counter4); 
    Serial.println(" ");

    
    // Print to TFT Display
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(10, 30);
    tft.print(dateTimeStr);

    delay(1000);
}


