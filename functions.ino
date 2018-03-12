//void printNumber(unsigned int number, byte numd) // print fixed-width uint number
//{
//  byte d=digits(number);
//  for(byte i=d; i<numd; ++i) lcd.print((char)' '); // padding
//  lcd.print(number);
//}

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
      if(!runInProgress) {
        if(DFRkeypad::KeyName(key) == "Up") {
          currentOption = currentOption + 1;
          if (currentOption > 1) {
            currentOption = 0;
          }
          lcd.print(menuOptions[currentOption]);
        }else if (DFRkeypad::KeyName(key) == "Down") {
          currentOption = currentOption - 1;
          if (currentOption < 0) {
            currentOption = 1;
          }
          lcd.print(menuOptions[currentOption]);
        }else if (DFRkeypad::KeyName(key) == "Select") {
           if (menuOptions[currentOption] == "INFO") {
            showInfo();
           }else if(menuOptions[currentOption] == "START") {
            runInProgress = true;
            sensorCounter = 0;
            startMillis = millis();
            createLoggingFile();
           }
        }
      }else {
        runInProgress = false;
        myFile.close();
      }
    }
  }
}

void createLoggingFile() {
  myFile = SD.open("rat.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println("testing 1, 2, 3.");
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void showInfo() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(softwareVersion);
  delay(5000);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("INFO");
}

