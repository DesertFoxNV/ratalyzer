// Libraries
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>
#include "DFRkeypad.h"
#include "HallEffectSensor.cpp"
#include <Wire.h>
#include <RtcDS3231.h>


// Global Variables
File myFile; //SD Card Variables
const int chipSelect = 4;
enum ePins { LCD_RS=8, LCD_EN=9, LCD_D4=11, LCD_D5=12, LCD_D6=6, LCD_D7=7, LCD_BL=10 }; //LCD Variables
byte lastKey=DFRkeypad::eINVALID_KEY;
float sum[DFRkeypad::eNUM_KEYS], sumq[DFRkeypad::eNUM_KEYS];  // arrays to sum up values for mean and deviation
unsigned int values[DFRkeypad::eNUM_KEYS];                    // counter for number of samples
unsigned long LastTime;
enum eSymbols { symPLUSMINUS=0 };                             // deviation LCD Symbol "+/-"
byte char_plusminus[8]=
  {
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00000,
  B11111,
  B00000,
  };

String menuOptions[2] = { "START", "INFO" };
int currentOption = 0;
String softwareVersion = "Version 1.0";
int sensorCounter = 0;
int lastByte = 1;
int currentValue;
long startMillis;
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7); // initialize the library with the numbers of the interface pins
RtcDS3231<TwoWire> Rtc(Wire);

HallEffectSensor hallEffectSensor0(37, 36, 35); 
boolean runInProgress = false;

void setup() {
//  serialConfig();
  sdCardConfig();
  displayConfig();
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  digitalWrite(18, LOW);
  digitalWrite(19, HIGH);
  Rtc.Begin();
  RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    Serial.println();
}
long count = 0;

void loop(void) {
  if(!hallEffectSensor0.read()){
    count++;
    RtcDateTime now = Rtc.GetDateTime();
    storeDateTime(now);
  }
//  if (runInProgress) {
//    currentValue = hallEffectSensor0.read();
//    if(!currentValue && lastByte) {
//       lastByte = currentValue;
//       sensorCounter = sensorCounter + 1;
//       myFile.println(millis());
//       myFile.println(",");
//       Serial.println(sensorCounter);
//    }
//    lastByte = currentValue;
//  } else {
//    readKeyPad();
//    if(sensorCounter) {
//      lcd.setCursor(0, 1);
//      lcd.print(sensorCounter);
//    }
//  }
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void storeDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    myFile = SD.open("test2.txt", FILE_WRITE);
    myFile.println(datestring);
    myFile.close();
    Serial.println("Done");
    lcd.setCursor(0, 1);
    lcd.print(count);
}

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}

