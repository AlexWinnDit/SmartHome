#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
Servo myservo;
#define RST_PIN          9          // Configurable, see typical pin layout above                                                                                                                                        //                         _____                        *                   ___    *  _____         
#define SS_PIN          10         // Configurable, see typical pin layout above                                                                                                                                         //          /\    |       |       \  /  \            /  |  |\   |  |\   |  |   \   |    |
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance                                                                                                                                                            //         /  \   |       |_____   \/    \    /\    /   |  | \  |  | \  |  |    \  |    |
byte uidCard[4] = {0xEC, 0x3C, 0x8E, 0xAB};                                                                                                                                                                              //        /----\  |       |        /\     \  /  \  /    |  |  \ |  |  \ |  |     ) |    |
//byte uidCard[4] = {0x36, 0x2D, 0xBA, 0x93};                                                                                                                                                                            //       /      \ |_____| |_____  /  \     \/    \/     |  |   \|  |   \|  |____/  |    |
int securityValue = 0;


#include <SoftwareSerial.h>
SoftwareSerial softSerial(7, 8); // RX, TX
const int buzzer = 6;
  
int secur = 0;
int d = 0; 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  softSerial.begin(9600);
  myservo.attach(5);
  myservo.write(180);
  pinMode (buzzer, OUTPUT);
  Serial.begin(9600);
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();
}
void loop() {
  Serial.print("ok");
  control();
  if (secur == 1) security();
  RFID();
  
  
  
}
void control()
{
  if (softSerial.available()){
      int com = softSerial.read();
      if (com == 'q') {DoorOP(); d = 1;}

      else if (com == 'a') {DoorCL(); d = 0;}
    
      else if (com == 's') secur = 1;

      else if (com == 'x') secur = 0;

      else if (com == 'y') securityValue = 0;
  }
}
void RFID()
{
  if (d == 0) //Открыть 
  {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;
 }
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;
 }    
        for (byte i = 0; i < 4; i++) {
          if ((uidCard[i] != mfrc522.uid.uidByte[i]))
          {             
                return;
          }
        }
          
        d = 1;
        softSerial.write('q');
        Serial.print('1');
        myservo.write(90);
        delay(1000);    
        
        
  }         
  
  if (d == 1) //Закрыть
  {
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;
 }
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;
 }    
        for (byte i = 0; i < 4; i++) {
          if ((uidCard[i] != mfrc522.uid.uidByte[i]))
          {             
                return;
          }
        }
          
        d = 0; 
        softSerial.write('a'); 
        Serial.println('2');
        myservo.write(180);
        delay(1000);
        
        
  
  }
}
void security()
{
   byte state = digitalRead(A2);
    while (state == 1){
      softSerial.write('t');
      securityValue = 1; 
      digitalWrite(buzzer, HIGH);
              control();
        if (securityValue == 0) state = 0;
        }
   digitalWrite(buzzer, LOW);
   delay (1000);
}


void DoorOP()
{
        myservo.write(90);
        softSerial.write('q');
        delay(1000);
}
void DoorCL()
{
        myservo.write(180);
        softSerial.write('a');
        delay(1000);
}

