
#include <Servo.h> 
#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9
#define SS_PIN 10
#define RST_PIN 9
#define PIN_OUT 4
#define ROW 3
#define COL 5

unsigned long lastTime;

int id_card[ROW][COL] = {
  {19, 158, 3, 248, 118},
  {51, 117, 94, 19, 11},
  {136, 5, 129, 157, 145}
};
RFID rfid(SS_PIN, RST_PIN); 

// Setup variables:
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;

Servo myServo; 
void setup() {
   myServo.attach(4); 
 Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  Serial.println("Ready");

}

void loop() {
   if (rfid.isCard()) {
        if (rfid.readCardSerial()) {
           
                /* With a new cardnumber, show it. */
                Serial.println(" ");
                Serial.println("Card found");
                serNum0 = rfid.serNum[0];
                serNum1 = rfid.serNum[1];
                serNum2 = rfid.serNum[2];
                serNum3 = rfid.serNum[3];
                serNum4 = rfid.serNum[4];

                //Serial.println(" ");
                Serial.println("Cardnumber:");
                Serial.print("Dec: ");
                Serial.print(rfid.serNum[0],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[1],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[2],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[3],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[4],DEC);
                Serial.println(" ");

                Serial.print("Hex: ");
                Serial.print(rfid.serNum[0],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[1],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[2],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[3],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[4],HEX);
                Serial.println(" ");
                 for (int r = 0; r < ROW; r++) 
                {
                  for (int c = 0; c < ROW*COL; c++) 
                  {
                    if (rfid.serNum[c] != id_card[r][c])
                      break;
                    else {
                      if (c == 4) {
                        servoOn();
                        Serial.println("masukk dalam looping");
                      }
                    }
                  }
                }
             
          }
    }

     if (millis() - lastTime >= 5000)
    servoOff();
    Serial.println("sampai sini");
}
 void servoOn(){
     myServo.write(180); 
     rfid.halt();
    delay(1000); 
  }
  void servoOff(){
      myServo.write(0);
      rfid.halt();
    delay(1000);
    }
    
