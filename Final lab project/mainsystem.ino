#include <SPI.h>
#include <Servo.h>
#include <LiquidCrystal.h>
////////////
const int rs = 12, en = 11, d4 = 14, d5 = 15, d6 = 16, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
////////////
#define SS1 22
#define SS2 23
#define SS3 24
#define fan1 30
#define fan2 31
#define fan3 32
#define RESET 19
boolean Working = false;

double temperature1 = 10;
double temperature2 = 50;
double temperature3 = 100;
int TotalTemperature = 0;
double Average = 0;
Servo myServo1;
Servo myServo2;
Servo myServo3;
int degree1 = 180;  
int degree2 = 180;  
int degree3 = 180;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Welcome !");
  
  Serial.begin(9600);
  Serial.println("Hello From Main System!");
  
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  pinMode(SS3, OUTPUT);

  pinMode(RESET , INPUT_PULLUP);
  
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);
  
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  digitalWrite(SS3, HIGH);
  
  SPI.begin();
 
  
  myServo1.attach(2,1000,2000);
  myServo2.attach(3,1000,2000);
  myServo3.attach(4,1000,2000);
}

void loop() {

 attachInterrupt(digitalPinToInterrupt(RESET), blink1, CHANGE);
state_changer();
printEverything();

 
}


void state_changer(){
   double Coefficient = random(2 , 3);
 //   int Coefficient2 = random(2 , 3);
  //   int Coefficient3 = random(2 , 2);
  if(temperature1 < 700 ){
    digitalWrite(fan1, LOW);
    degree1 = 180;
    myServo1.write(degree1);
    temperature1 += (Coefficient * temperature1 )/2;
    Working = true;
  }
   if(temperature2 < 700 ){
    digitalWrite(fan2, LOW);
    degree2 = 180;
    myServo2.write(degree2);
       temperature2 += (Coefficient * temperature2 )/2;
        Working = true;
  }
   if(temperature3 < 700 ){
    digitalWrite(fan2, LOW);
    degree3 = 180;
    myServo3.write(degree3);
       temperature3 += (Coefficient * temperature3 )/2;
        Working = true;
  }
  if(Working){
      lcd.clear();
      lcd.print("System is Working!");
  }
        
  TotalTemperature =  temperature1 + temperature2 + temperature3;
  Average = TotalTemperature / 3;
  if(Average >= 500){
    inform_others();
    
  }
      if(temperature1 >= 300){
        degree1 = 90;
        digitalWrite(fan1, HIGH);
        myServo1.write(degree1);
        delay(200);
        temperature1 -= 50;
        Serial.println();
        Serial.println("Temperature 1 After cooling");
        Serial.print("to 50 degrees by fan : ");
        Serial.println(temperature1);
        
      }
      if(temperature2 >= 300){
        degree2 = 90;
        myServo2.write(degree2);
        delay(200);
        temperature2 -= 50;
        Serial.println();
        Serial.println("Temperature 2 After cooling");
        Serial.print("to 50 degrees by fan : ");
        Serial.println(temperature2);
      }
      if(temperature3 >= 300){
        degree3 = 90;
        digitalWrite(fan3, HIGH);
        myServo3.write(degree3);
        delay(200);
        temperature3 -= 50;
        Serial.println();
        Serial.println("Temperature 3 After cooling ");
        Serial.print("to 50 degrees by fan : ");
        Serial.println(temperature3);
      }
      

}



void inform_slaves(int data, int CS_pin){
  // put the CS_pin low to activate the connection
  digitalWrite(CS_pin, LOW);
  delay(100);
  SPI.transfer(data);
  delay(100);
  // put the CS_pin high to deactivate the connection
  digitalWrite(CS_pin, HIGH);
}

// this function informs all slaves to shut down quickly in order to be safe
void inform_others(){

   degree1 = 0;
   myServo1.write(degree1);


   degree2 = 0;
    myServo2.write(degree2);

 
   degree3 = 0;
   myServo3.write(degree3);
    lcd.clear();
    lcd.print("Shiting Down Everything!");
 
  inform_slaves(1, SS1);
  inform_slaves(1, SS2);
  inform_slaves(1, SS3);
  
  inform_slaves(0, SS1);
  inform_slaves(0, SS2);
  inform_slaves(0, SS3);
  

}
void printEverything(){
   Serial.print("Temperature 1 is: ");
  Serial.println(temperature1);
  delay(200);

  Serial.print("Temperature 2 is: ");
  Serial.println(temperature2);
  delay(200);

  Serial.print("Temperature 3 is: ");
  Serial.println(temperature3);
  delay(200);

  
  Serial.print("Avarage  is: ");
  Serial.println(Average);
  delay(200);
  Serial.println();
}

void resetState(){
   Serial.println("reseting ...!");
    temperature1 = 10;
    temperature2 = 15;
    temperature3 = 20;
    degree1 = 180;
    degree2 = 180;
    degree3 = 180;
    myServo1.write(degree1);
    myServo2.write(degree2);
    myServo3.write(degree2);
}
void blink1(){
  resetState();
  }
