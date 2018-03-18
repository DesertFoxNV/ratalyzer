void serialConfig() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void sdCardConfig() {
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(SS, OUTPUT);
   
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void displayConfig() {
  lcd.begin(16, 2);                               // set up the LCD's number of columns and rows (16x2)
  lcd.createChar(symPLUSMINUS, char_plusminus);   // create +/- character

  pinMode(lcdBacklight, OUTPUT);                        // pin LCD_BL is LCD backlight brightness (PWM)
  analogWrite(lcdBacklight, 255);                       // set the PWM brightness to maximum
  lcd.setCursor(0, 0);
  lcd.print("Ratalyzer (Menu)");
  lcd.setCursor(0, 1);
  lcd.print("START");

  DFRkeypad::FastADC(true);                        // increase ADC sample frequency
  DFRkeypad::iDEFAULT_THRESHOLD=140;              // maximum threshold acceptable so bounds in DFRkeypad::iARV_VALUES are not overlapping
  clearStat();                                    // clear statistics
  LastTime=millis();                              // remember tick counter
}

void clockConfig() {
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  digitalWrite(18, LOW);
  digitalWrite(19, HIGH);
  Rtc.Begin();
}



