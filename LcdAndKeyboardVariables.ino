// Global Variables LCD and Keyboard

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

String menuOptions[3] = { "START", "INFO", "TEST"};
int currentOption = 0;
