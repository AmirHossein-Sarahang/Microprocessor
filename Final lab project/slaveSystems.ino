#include <SPI.h>

uint8_t transfer_data;
boolean received;

const int ledPin = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello From Slave Systems !");
  pinMode(MISO, OUTPUT);
  digitalWrite(MISO,LOW);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
  received = false;

  pinMode(ledPin,OUTPUT);
}

void loop() {
    if (received){
      if (transfer_data != 0){
          digitalWrite(ledPin,HIGH);
          
  tone(50, 1000, 300);
          Serial.println("Shuting down !!!1");
          Serial.println("Cooling... ");
           delay(500);

        }
      else if (transfer_data == 0){
          digitalWrite(ledPin,LOW);
      }
    }

    delay(100);
}

ISR (SPI_STC_vect){
  transfer_data = SPDR; 
  received = true;
}
