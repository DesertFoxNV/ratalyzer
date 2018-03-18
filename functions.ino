byte digits(unsigned int iNum) // calculate the number of digits
{
  byte bDigits=0;
  do
  {
    ++bDigits;
    iNum/=10;
  } while(iNum);
  return bDigits;
}

void clearStat() // clear statistics
{
  memset(sum, 0, sizeof(sum));
  memset(sumq, 0, sizeof(sumq));
  memset(values, 0, sizeof(values));
}

void readKeyPad() {
  byte key=DFRkeypad::GetKey();                   // read a key identifier


  if(DFRkeypad::eNO_KEY<key && key<DFRkeypad::eINVALID_KEY) // if a valid key has been identified
  {
    int val=analogRead(KEYPAD);                             // ... get the analog value for it
    sum[key]+=val;                                          // add val into array
    sumq[key]+=(float)val*(float)val;                       // add val^2 into array
    ++values[key];                                          // increase sample counter

    if(millis()>LastTime+1000)                              // if sampled for one second...
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      if(!recordData && !testing) {
        if(DFRkeypad::KeyName(key) == "Up" || DFRkeypad::KeyName(key) == "Right") {
          currentOption = currentOption + 1;
          if (currentOption >= sizeof(menuOptions) / sizeof(menuOptions[0])) {
            currentOption = 0;
          }
          lcd.print(menuOptions[currentOption]);
        }else if (DFRkeypad::KeyName(key) == "Down" || DFRkeypad::KeyName(key) == "Left") {
          currentOption = currentOption - 1;
          if (currentOption < 0) {
            currentOption = sizeof(menuOptions) / sizeof(menuOptions[0]) - 1;
          }
          lcd.print(menuOptions[currentOption]);
        }else if (DFRkeypad::KeyName(key) == "Select") {
           if (menuOptions[currentOption] == "INFO") {
              showInfo();
           }else if(menuOptions[currentOption] == "START") {
              startTest();
           } else if(menuOptions[currentOption] == "TEST") {
              testDevice();
           }
        }
      }else {
        Serial.println("Menu State");
        lcd.setCursor(0, 0);
        lcd.print("Ratalyzer (Menu)");
        testing = false;
        recordData = false;
      }
    }
  }
}

void testDevice() {
  count = 0;
  testing = true;
  lcd.setCursor(0, 0);
  lcd.print("Ratalyzer (Test)");
}

void startTest() {
  count = 0;
  recordData = true;

  RtcDateTime now = Rtc.GetDateTime();
  currentFileName = getDate(now, 1);
  
  Serial.println(currentFileName);
  
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print(getDate(now));
  
  currentFileName = currentFileName + ".csv";
  char fileName[sizeof(currentFileName)];
  currentFileName.toCharArray(fileName, sizeof(fileName));

  myFile = SD.open(fileName, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println(getDate(now) + ",");
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    clearLine(0);
    clearLine(1);
    lcd.setCursor(0, 0);
    lcd.print("Error: FileWrite");
  }
}

void clearLine(int lineNumber){
  lcd.setCursor(0, lineNumber);
  lcd.print("                ");
}

void showInfo() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(softwareVersion);
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("INFO");
}

void collectData() {
  if (recordData){
    printCount();
  }
}

void test() {
  if(testing) {
    printCount();
  }
}

void printCount() {
  byte sensorResult = hallEffectSensor0.read();
    if(!sensorResult && lastByte){
    count++;
    lastReadingMillis = millis();
    lcd.setCursor(0, 1);
    lcd.print(count);
    
      if (!checkKeyPad){
        lcd.print("-MD");
      }

      if(recordData){
        addData();
      }
    }
    lastByte = sensorResult;

    if(millis() - lastReadingMillis > 5000) {
      if (clearPrint) {
        lcd.setCursor(0, 1);
        lcd.print(count);
        lcd.print("   ");
      }
      clearPrint = false;
      checkKeyPad = true;
    } else {
      lcd.setCursor(0, 1);
      lcd.print(count);
      lcd.print("-MD");
      clearPrint = true;
      checkKeyPad = false;
    }
}

void addData() {
  RtcDateTime now = Rtc.GetDateTime();

  char fileName[sizeof(currentFileName)];
  currentFileName.toCharArray(fileName, sizeof(fileName));
  
  myFile = SD.open(fileName, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println(getDate(now) + ",");
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    clearLine(0);
    clearLine(1);
    lcd.setCursor(0, 0);
    lcd.print("Error: FileWrite");
  }
}

