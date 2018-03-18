// Libraries
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>
#include "DFRkeypad.h"
#include "HallEffectSensor.cpp"
#include <Wire.h>
#include <RtcDS3231.h>


// Global Variables
File myFile; //SD Card File
const int chipSelect = 4; //SD Card

String softwareVersion = "Version 1.0";

int sensorCounter = 0;
long count = 0;
int lastByte = 1;
int currentValue;
long startMillis;
long lastReadingMillis;
String currentFileName;
boolean clearPrint = true;

//Loop States
boolean checkKeyPad = true; //Keypad Buttons Active
boolean testing = false; //Test Mode
boolean recordData = false; //Data Collection Mode

int lcdBacklight = 10;

LiquidCrystal lcd(8, 9, 11, 12, 6, 7); // initialize the library with the numbers of the interface pins
RtcDS3231<TwoWire> Rtc(Wire);

HallEffectSensor hallEffectSensor0(37, 36, 35); 

void setup() {
  //serialConfig();
  sdCardConfig();
  displayConfig();
  clockConfig();
}

void loop(void) {
  if(testing) {
    test();
  } 
  
  if(checkKeyPad) {
    readKeyPad();
  }

  if(recordData) {
    collectData();
  }
}

