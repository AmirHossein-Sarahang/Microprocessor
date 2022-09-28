
#include <Keypad.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 14, d5 = 15, d6 = 16, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  
  Serial.begin(9600);
   lcd.begin(16, 2);
  
}
  
void loop(){
   
  
    
  char key = "" ; 
  key = keypad.waitForKey();
  int YazdanKey = key - '0' + 40;
  lcd.print(YazdanKey);
  Serial.write(YazdanKey);
  delay(500);
//  if(Serial.available()>0){
 //   lcd.print("Try again Yazdan :)"); 
   

 //   key = "";
 //   key = keypad.waitForKey();
  //   int YazdanKey = key - '0' + 40;
  //   lcd.print(YazdanKey);
  //    Serial.write(YazdanKey);
  //   delay(500);
//  }
   
  
}
