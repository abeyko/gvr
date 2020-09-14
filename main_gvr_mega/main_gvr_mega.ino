// Import Adafruit Liquid Crystal library
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 

// Define touch sensor Arduino Mega pins
#define touchPinRight 52
#define touchPinLeft 50

// Begin category image array assignments
#define ARRAY_SIZE 12

String str = "";
int str_len = 0;
char char_array[64];

// Create LCD objects
LiquidCrystal lcd1(7, 41, 9, 10, 11, 12); // level
LiquidCrystal lcd2(7, 43, 9, 10, 11, 12); // phonetic spelling
LiquidCrystal lcd3(7, 45, 9, 10, 11, 12); // "categories"
LiquidCrystal lcd4(7, 47, 9, 10, 11, 12); // menu option 1
LiquidCrystal lcd5(7, 49, 9, 10, 11, 12); // menu option 2
LiquidCrystal lcd6(7, 51, 9, 10, 11, 12); // menu option 3
LiquidCrystal lcd7(7, 53, 9, 10, 11, 12); // menu option 4

// Declare boolean variables
bool gameStarted = false;
bool advanceTheRound = false;

bool rightActive = false;
bool leftActive = false;

bool page1 = true;
bool page2 = false;

bool gameOver = false;

// Declare button integer variables
const int tftButton1 = 22;
const int tftButton2 = 24;
const int tftButton3 = 26;
const int tftButton4 = 28;

const int lcdButton4 = 30;
const int lcdButton5 = 32;
const int lcdButton6 = 34;
const int lcdButton7 = 36;

int correctTftButtonState = 0;

int tftButtonState1 = 0;
int tftButtonState2 = 0;
int tftButtonState3 = 0;
int tftButtonState4 = 0;

int tftButtonCheck = 1;

int lcdButtonState4 = 0;
int lcdButtonState5 = 0;
int lcdButtonState6 = 0;
int lcdButtonState7 = 0;

int categorySelected = 0;

int allWordsArray[] = {0,1,2,3,4,5,6,7,8,9,10,11};
int allWordsMaxCount = 12;
int allWordsRemainder = 99;
int allWordsRemainderPosition = 99;
int allWordsIndexPosition = 99;
long allWordsRandomNumber = 99;

int allWordsArrayCopy[] = {0,1,2,3,4,5,6,7,8,9,10,11};
int allWordsMaxCountCopy = 12;

String phoneticSpelling = "";
String soundFile = "";
String correctWord = "";
String incorrectWordOne = "";
String incorrectWordTwo = "";
String incorrectWordThree = "";

int screenAssignmentArray[] = {0,1,2,3};
int screenAssignmentMaxCount = 4;
int screenAssignmentRemainder = 99;
int screenRemainderPosition = 99;
int screenIndexPosition = 99;
long screenAssignmentRandomNumber = 99;

char *categories[] = {
  "ADJECTIVES", 
  "ANIMALS", 
  "BODY PARTS",
  "COLORS", 
  "DIRECTIONS", 
  "FOOD",
  "PEOPLE",
  "VERBS"
};

String adjectivesImages[ARRAY_SIZE] = { 
  "ad_bad", 
  "ad_big", 
  "ad_cold",
  "ad_conf",
  "ad_fast",
  "ad_funn",
  "ad_good",
  "ad_hot",
  "ad_shor",
  "ad_slow",
  "ad_smal",
  "ad_tall"
};

String adjectivesSounds[ARRAY_SIZE] = {
  "words/adjectives/adj00001.mp3", 
  "words/adjectives/adj00002.mp3", 
  "words/adjectives/adj00003.mp3",
  "words/adjectives/adj00004.mp3", 
  "words/adjectives/adj00005.mp3", 
  "words/adjectives/adj00006.mp3",
  "words/adjectives/adj00007.mp3",
  "words/adjectives/adj00008.mp3",
  "words/adjectives/adj00009.mp3",
  "words/adjectives/adj00010.mp3",
  "words/adjectives/adj00011.mp3",
  "words/adjectives/adj00012.mp3"
};

String adjectivesPhonetics[ARRAY_SIZE] = {
  "KAKO", 
  "MEGALO", 
  "KRYO",
  "VEVAIOS", 
  "GRIGORA", 
  "ASTEIOS",
  "KALOS",
  "ZESTO",
  "KONTOS",
  "SIGANOS",
  "MIKRO",
  "PSILOS"
};

String animalsImages[ARRAY_SIZE] = { 
  "an_cat", 
  "an_chck", 
  "an_chkn",
  "an_cow",
  "an_dog",
  "an_duck",
  "an_dklg",
  "an_goat",
  "an_hen",
  "an_hipp",
  "an_kitt",
  "an_pupp"
};

String bodyPartsImages[ARRAY_SIZE] = { 
  "bp_bell", 
  "bp_chee", 
  "bp_ches",
  "bp_ear",
  "bp_brow",
  "bp_face",
  "bp_fing",
  "bp_foot",
  "bp_hair",
  "bp_hand",
  "bp_mout",
  "bp_nose"
};

String colorsImages[ARRAY_SIZE] = { 
  "co_blac", 
  "co_blue", 
  "co_brow",
  "co_gray",
  "co_gree",
  "co_oran",
  "co_pink",
  "co_purp",
  "co_red",
  "co_silv",
  "co_whit",
  "co_yell"
};

String directionsImages[ARRAY_SIZE] = { 
  "di_afte", 
  "di_ahea", 
  "di_befo",
  "di_behi",
  "di_curv",
  "di_down",
  "di_left",
  "di_over",
  "di_righ",
  "di_stra",
  "di_unde",
  "di_up"
};

String foodImages[ARRAY_SIZE] = { 
  "fo_appl", 
  "fo_bana", 
  "fo_cucu",
  "fo_grap",
  "fo_lemo",
  "fo_lime",
  "fo_melo",
  "fo_oran",
  "fo_pear",
  "fo_stra",
  "fo_toma",
  "fo_wate"
};

String peopleImages[ARRAY_SIZE] = { 
  "pe_baby", 
  "pe_boy", 
  "pe_chil",
  "pe_dad",
  "pe_fath",
  "pe_girl",
  "pe_grfa",
  "pe_grma",
  "pe_libo",
  "pe_ligr",
  "pe_mom",
  "pe_mthr"
};

String verbsImages[ARRAY_SIZE] = { 
  "ve_come", 
  "ve_drin", 
  "ve_eat",
  "ve_fly",
  "ve_give",
  "ve_need",
  "ve_run",
  "ve_see",
  "ve_swim",
  "ve_take",
  "ve_walk",
  "ve_want"
};
  
void setup() {
  // 9600
  Serial.begin(9600); // Serial Pins on Mega: 0(RX), 1(TX) - for sending messages to TFT 1
  
  // 19200
  Serial1.begin(19200); // Serial 1 Pins on Mega: 19(RX), 18(TX) - for sending messages to TFT 2
  
  // 38400
  Serial2.begin(38400); // Serial 2 Pins on Mega: 17(RX), 16(TX) - for sending messages to TFT 3
  
  //  57600
  Serial3.begin(57600); // Serial 3 Pins on Mega: 15(RX), 14(TX) - for sending messages to TFT 4

  str = "<";
  str += "ad_conf";
  str += ">";
  str_len = str.length() + 1;
  char_array[str_len];
  str.toCharArray(char_array, str_len);
  Serial.write(char_array, str_len);
  Serial1.write(char_array, str_len);
  Serial2.write(char_array, str_len);
  Serial3.write(char_array, str_len);

  randomSeed(analogRead(A0)); // A0 is a floating value

  pinMode(touchPinRight, INPUT);
  pinMode(touchPinLeft, INPUT);
  
  pinMode(tftButton1, INPUT_PULLUP);
  pinMode(tftButton2, INPUT_PULLUP);
  pinMode(tftButton3, INPUT_PULLUP);
  pinMode(tftButton4, INPUT_PULLUP);
  
  pinMode(lcdButton4, INPUT_PULLUP);
  pinMode(lcdButton5, INPUT_PULLUP);
  pinMode(lcdButton6, INPUT_PULLUP);
  pinMode(lcdButton7, INPUT_PULLUP);

  lcd1.begin(16,2); 
  lcd2.begin(16,2);
  lcd3.begin(16,2);
  lcd4.begin(16,2);
  lcd5.begin(16,2);
  lcd6.begin(16,2);
  lcd7.begin(16,2);
  
  lcd1.print("LEVEL 1");
  lcd2.print("LOADING...");
  lcd3.print("CATEGORIES");
  lcd4.print("ADJECTIVES");
  lcd5.print("ANIMALS");
  lcd6.print("BODY PARTS");
  lcd7.print("COLORS");
}

void loop() {
//  if (!gameStarted) {
//    updateMenu();
//    checkLCDButtons();
//  }
//  else if (gameStarted) {
//    if (!gameOver) {
//      runMainProgram();
//    }
//  }
}

void rightTouched() {
  clearMenuScreens();
  leftActive = false;
  rightActive = true;
}

void leftTouched() {
  clearMenuScreens();
  rightActive = false;
  leftActive = true;
}

void rightMenuActive() {
    lcd4.print("DIRECTIONS");
    lcd5.print("FOOD");
    lcd6.print("PEOPLE");
    lcd7.print("VERBS");
    leftActive = false;
    rightActive = false;
    page1 = false;
    page2 = true;
}

void leftMenuActive() {
    lcd4.print("ADJECTIVES");
    lcd5.print("ANIMALS");
    lcd6.print("BODY PARTS");
    lcd7.print("COLORS");
    leftActive = false;
    rightActive = false;
    page2 = false;
    page1 = true;
}

void updateMenu() {
  int touchPinRightValue = digitalRead(touchPinRight);
  int touchPinLeftValue = digitalRead(touchPinLeft);
  if (touchPinRightValue == HIGH) {
//    Serial.println("MENU PAGE 2");
    rightTouched();
  } 
  else if (touchPinLeftValue == HIGH) {
//    Serial.println("MENU PAGE 1");
    leftTouched();
  }

  if (rightActive) {
    rightMenuActive();
  }
  else if (leftActive) {
    leftMenuActive();
  }
}

void checkLCDButtons() {
  lcdButtonState4 = digitalRead(lcdButton4);
  lcdButtonState5 = digitalRead(lcdButton5);
  lcdButtonState6 = digitalRead(lcdButton6);
  lcdButtonState7 = digitalRead(lcdButton7);
  if (lcdButtonState4 == LOW or lcdButtonState5 == LOW or lcdButtonState6 == LOW or lcdButtonState6 == LOW ) {
    lcdButtonPressed();
    startGame();
  }
}

void checkTFTButtons() {
//  Serial.println("TFT BUTTON CHECK: ");
//  Serial.println(tftButtonCheck);
  while (!advanceTheRound) {
    tftButtonState1 = digitalRead(tftButton1);
    tftButtonState2 = digitalRead(tftButton2);
    tftButtonState3 = digitalRead(tftButton3);
    tftButtonState4 = digitalRead(tftButton4);
    if (tftButtonState1 == LOW or tftButtonState2 == LOW or tftButtonState3 == LOW or tftButtonState4 == LOW ) {
      tftButtonPressed();
    }
  }
}

void lcdButtonPressed() {
  if (page1) {
    if (lcdButtonState4 == LOW) {
      categorySelected = 1; // Adjectives Selected
    }
    else if (lcdButtonState5 == LOW) {
      categorySelected = 2; // Animals Selected
    }
    else if (lcdButtonState6 == LOW) {
      categorySelected = 3; // Body Parts Selected
    }
    else if (lcdButtonState7 == LOW) {
      categorySelected = 4; // Colors Selected
    }
  } 

  else if (page2) {
    if (lcdButtonState4 == LOW) {
      categorySelected = 5; // Directions Selected
    }
    else if (lcdButtonState5 == LOW) {
      categorySelected = 6; // Food Selected
    }
    else if (lcdButtonState6 == LOW) {
      categorySelected = 7; // People Selected
    }
    else if (lcdButtonState7 == LOW) {
      categorySelected = 8; // Verbs Selected
    }
  }
}

void tftButtonPressed() {
//  Serial.println("A TFT BUTTON PRESSED");
  if (tftButtonCheck == 1) {
    if (tftButtonState1 == LOW) {
//      Serial.println("Correct Button Pressed!");
      advanceTheRound = true;
    }
    if (tftButtonState2 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
    if (tftButtonState3 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
    if (tftButtonState4 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
  } else if (tftButtonCheck == 2) {
    if (tftButtonState2 == LOW) {
//      Serial.println("Correct Button Pressed!");
      advanceTheRound = true;
    }
    if (tftButtonState1 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
    if (tftButtonState3 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
    if (tftButtonState4 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
  } else if (tftButtonCheck == 3 && tftButtonState3 == LOW) {
    if (tftButtonState3 == LOW) {
//      Serial.println("Correct Button Pressed!");
      advanceTheRound = true;
    }
    if (tftButtonState1 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
    if (tftButtonState2 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
    if (tftButtonState4 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
  } else if (tftButtonCheck == 4 && tftButtonState4 == LOW) {
    if (tftButtonState4 == LOW) {
//      Serial.println("Correct Button Pressed!");
      advanceTheRound = true;
    }
    if (tftButtonState1 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
    if (tftButtonState2 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
    if (tftButtonState3 == LOW) {
//      Serial.println("Incorrect Button Pressed");
      advanceTheRound = true;
    }
  }
}

void runMainProgram() {
  for (int a=0; a<6; a++) {
//    Serial.println("ROUND");
//    Serial.println(a+1);
    allWordsRandomNumber = random(1, 109);
//    Serial.println("ALL WORDS RANDOM NUMBER");
//    Serial.println(allWordsRandomNumber);
    allWordsRemainder = allWordsRandomNumber % allWordsMaxCount;
//    Serial.println("ALL WORDS REMAINDER");
//    Serial.println(allWordsRemainder);
    for (int b=0; b<12; b++) {
      if (allWordsArray[b] == allWordsRemainder) {
        allWordsRemainderPosition = b;
      }
    }
    correctWord = adjectivesImages[allWordsRemainderPosition];
    phoneticSpelling = adjectivesPhonetics[allWordsRemainderPosition];
    clearPhoneticScreen();
    lcd2.print(phoneticSpelling);
    soundFile = adjectivesSounds[allWordsRemainderPosition];
    for (int c = 0; c < allWordsMaxCount; c++) {
      for (int d = 0; d < 12; d++) {
        if (allWordsArray[d] == c) {
          allWordsIndexPosition = d;
        }
      }
      if (c < allWordsRemainder) {
        allWordsArray[allWordsIndexPosition] = c; // doesn't change
      } else if (c == allWordsRemainder) {
        allWordsArray[allWordsIndexPosition] = 99; // set equal to 99
      } else if (c > allWordsRemainder) {
        allWordsArray[allWordsIndexPosition] = c-1; // reduce value by 1
      }        
    }
    allWordsMaxCount--;
    allWordsMaxCountCopy = allWordsMaxCount;
    for (int e=0; e<12; e++) {
      allWordsArrayCopy[e] = allWordsArray[e];
    }
    for (int f=0; f<3; f++) {
      allWordsRandomNumber = random(1, 109);
      allWordsRemainder = allWordsRandomNumber % allWordsMaxCountCopy;
      for (int g=0; g<12; g++) {
        if (allWordsArrayCopy[g] == allWordsRemainder) {
          allWordsRemainderPosition = g;
        }
      }
      if (f == 0) {
        incorrectWordOne = adjectivesImages[allWordsRemainderPosition];
      } else if (f == 1) {
        incorrectWordTwo = adjectivesImages[allWordsRemainderPosition];
      } else if (f == 2) {
        incorrectWordThree = adjectivesImages[allWordsRemainderPosition];
      }
      for (int h = 0; h < allWordsMaxCountCopy; h++) {
        for (int i = 0; i < 12; i++) {
          if (allWordsArrayCopy[i] == h) {
            allWordsIndexPosition = i;
          }
        }
        if (h < allWordsRemainder) {
          allWordsArrayCopy[allWordsIndexPosition] = h; // doesn't change
        } else if (h == allWordsRemainder) {
          allWordsArrayCopy[allWordsIndexPosition] = 99; // set equal to 99
        } else if (h > allWordsRemainder) {
          allWordsArrayCopy[allWordsIndexPosition] = h-1; // reduce value by 1
        }  
      }
      allWordsMaxCountCopy--;
    }
    // screen assignment loop
    for (int j=0; j<4; j++) {
      screenAssignmentRandomNumber = random(1, 109);
      screenAssignmentRemainder = screenAssignmentRandomNumber % screenAssignmentMaxCount;
      for (int k=0; k<4; k++) {
        if (screenAssignmentArray[k] == screenAssignmentRemainder) {
          screenRemainderPosition = k;
        }
      }
//      Serial.println("SCREEN ASSIGNMENT MAX COUNT: ");
//      Serial.println(screenAssignmentMaxCount);
      if (screenAssignmentMaxCount == 4) {
        if (screenRemainderPosition == 0) {  
          str = "<";
          str += correctWord;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial.write(char_array, str_len);
          tftButtonCheck = 1;
        } else if (screenRemainderPosition == 1) {
          str = "<";
          str += correctWord;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial1.write(char_array, str_len);
          tftButtonCheck = 2;
        } else if (screenRemainderPosition == 2) {
          str = "<";
          str += correctWord;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial2.write(char_array, str_len);
          tftButtonCheck = 3;
        } else if (screenRemainderPosition == 3) {
          str = "<";
          str += correctWord;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial3.write(char_array, str_len);
          tftButtonCheck = 4;
        }
      } else if (screenAssignmentMaxCount == 3) {
        if (screenRemainderPosition == 0) {
          str = "<";
          str += incorrectWordOne;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial.write(char_array, str_len);
        } else if (screenRemainderPosition == 1) {
          str = "<";
          str += incorrectWordOne;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial1.write(char_array, str_len);
        } else if (screenRemainderPosition == 2) {
//          Serial.println("ROUND ");
          str = '<' + incorrectWordOne + '>';
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial2.write(char_array, str_len);
        } else if (screenRemainderPosition == 3) {
          str = "<";
          str += incorrectWordOne;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial3.write(char_array, str_len);
        }
      } else if (screenAssignmentMaxCount == 2) {
        if (screenRemainderPosition == 0) {
          str = "<";
          str += incorrectWordTwo;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial.write(char_array, str_len);
        } else if (screenRemainderPosition == 1) {
          str = "<"; 
          str += incorrectWordTwo;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial1.write(char_array, str_len);
        } else if (screenRemainderPosition == 2) {
          str = "<";
          str += incorrectWordTwo;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial2.write(char_array, str_len);
        } else if (screenRemainderPosition == 3) {
          str = "<";
          str += incorrectWordTwo;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial3.write(char_array, str_len);
        }
      } else if (screenAssignmentMaxCount == 1) {
        // assign incorrectWord3
        if (screenRemainderPosition == 0) {
          str = "<";
          str += incorrectWordThree;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial.write(char_array, str_len);
        } else if (screenRemainderPosition == 1) {
          str = "<";
          str += incorrectWordThree;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial1.write(char_array, str_len);
        } else if (screenRemainderPosition == 2) {
          str = "<";
          str += incorrectWordThree;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial2.write(char_array, str_len);
        } else if (screenRemainderPosition == 3) {
          str = "<";
          str += incorrectWordThree;
          str += ">";
          str_len = str.length() + 1;
          char_array[str_len];
          str.toCharArray(char_array, str_len);
          Serial3.write(char_array, str_len);
        }
      }
      for (int l = 0; l < screenAssignmentMaxCount; l++) {
        for (int m = 0; m < 4; m++) {
          if (screenAssignmentArray[m] == l) {
            screenIndexPosition = m;
          }
        }
        if (l < screenAssignmentRemainder) {
          screenAssignmentArray[screenIndexPosition] = l; // doesn't change
        } else if (l == screenAssignmentRemainder) {
          screenAssignmentArray[screenIndexPosition] = 99; // set equal to 99
        } else if (l > screenAssignmentRemainder) {
          screenAssignmentArray[screenIndexPosition] = l-1; // reduce value by 1
        }        
      }
      screenAssignmentMaxCount--;
    } // end of screen assignment loop
    for (int m = 0; m < 4; m++) {
      screenAssignmentArray[m] = m;
    }
    screenAssignmentMaxCount = 4;
    checkTFTButtons();
    advanceTheRound = false;
  } // end of round loop

//  if (categorySelected == 1) {
//  } else if (categorySelected == 2) {
//    Serial.println("Selecting random word from animals category");
//  } else if (categorySelected == 3) {
//    Serial.println("Selecting random word from body parts category");
//  } else if (categorySelected == 4) {
//    Serial.println("Selecting random word from colors category");
//  } else if (categorySelected == 5) {
//    Serial.println("Selecting random word from directions category");
//  } else if (categorySelected == 6) {
//    Serial.println("Selecting random word from food category");
//  } else if (categorySelected == 7) {
//    Serial.println("Selecting random word from people category");
//  } else if (categorySelected == 8) {
//    Serial.println("Selecting random word from verbs category");
//  }

  gameOver = true;
} // end of runMainProgram function declaration

void clearMenuScreens() {
  lcd4.clear();
  lcd5.clear();
  lcd6.clear();
  lcd7.clear();
}

void clearPhoneticScreen() {
  lcd2.clear();
}

void startGame() {
  gameStarted = true;
}

