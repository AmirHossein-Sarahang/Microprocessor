
#include <Keypad.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 14, d5 = 15, d6 = 16, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9}; //connect to the column pinouts of the keypad
int board[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);

  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);

  int counter = 1;

  while (counter < 20) {
    
    
    if (counter % 2 == 1 ) {

      
     
      delay(200);
      char GhazalKey = keypad.waitForKey();
      int intkey = (GhazalKey - '0') + 30;
      delay(200);

      
      if((board[intkey - 31] == 1) ||(board[intkey - 31] == 0)){
          boolean test = true;
          int cnt = 0;
           while(test != false){
               delay(100);
               lcd.clear();
               lcd.print("Try again Ghazal :)");
               delay(300);
               lcd.clear();
               GhazalKey = "";
               GhazalKey = keypad.waitForKey();
               intkey = 0;
               intkey = (GhazalKey - '0') + 30;
               if((board[intkey - 31] != 1) && (board[intkey - 31] != 0)){
                  intkey = GhazalKey - '0' + 30;
                  test = false;
                  lcd.print("00");
                }
           cnt++;
          }
     }

      
      board[intkey - 31] = 1;
      GhazalKey = "";
     
      digitalWrite(intkey , HIGH);

    }
    delay(2000);
    if (counter % 2 == 0 ) {
      if (Serial.available() > 0) {
        int YK = Serial.read();
        /////
        
   //      if((board[YK  - 41] == 1) ||(board[YK  - 41] == 0)){
   //            lcd.clear();
   //            lcd.print("Try again Yazdan :)");
   //            delay(500);
   //            lcd.clear();
   //            delay(500);
   //            YK = 0;
   //             if (Serial.available() > 0) {
   //             int YK = Serial.read();
   //             
    //            }
 
    //      }
        
        
        digitalWrite(YK, HIGH);
         board[YK - 41] = 0;
      }

    }
    
  //    lcd.clear();
  //    lcd.print("*");
  //   lcd.print(board[0]);
  //   lcd.print("*");
    
    counter++;
    isFinished();
  }

}

void loop() {}

void isFinished(){
  if(board[0] ==  board[3] && board[3] == board[6]){
    if(board[0] == 1){
      lcd.clear();
      lcd.print("Ghazal won ! :)");
    }
    else{
       lcd.clear();
        lcd.print("1");
       lcd.print("Yazdan won ! :)");
    }
  }
  if(board[0] ==  board[1] &&  board[1] == board[2]){
    if(board[0] == 1){
      lcd.clear();
      lcd.print("Ghazal won ! :)");
    }
    else{
       lcd.clear();
       lcd.print("Yazdan won ! :)");
    }
  }
  if(board[2] ==  board[5] && board[5] == board[8]){
    if(board[2] == 1){
      lcd.clear();
      lcd.print("Ghazal won ! :)");
    }
    else{
       lcd.clear();
       lcd.print("Yazdan won ! :)");
    }
  }
  if(board[6] ==  board[7] && board[7] == board[8]){
    lcd.print("4");
    if(board[6] == 1){
      lcd.clear();
      lcd.print("Ghazal won ! :)");
    }
    else{
       lcd.clear();
       lcd.print("Yazdan won ! :)");
    }
  }
  if(board[2] ==  board[4] && board[4] == board[6]){
    
    if(board[2] == 1){
      lcd.clear();
      lcd.print("Ghazal won ! :)");
    }
    else{
       lcd.clear();
       lcd.print("Yazdan won ! :)");
    }
  }
  if(board[0] ==  board[4] && board[4] == board[8]){
     
    if(board[0] == 1){
      lcd.clear();
      lcd.print("Ghazal won ! :)");
    }
    else{
        lcd.clear();
       lcd.print("Yazdan won ! :)");
    }
  }
  
}
