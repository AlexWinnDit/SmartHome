#include <EtherCard.h>  // Подключаем скачанную библиотеку. https://yadi.sk/d/R57sVoglbhTRN
static byte mymac[] = { 
  0x5A,0x5A,0x5A,0x5A,0x5A,0x5A };

// ip статический / постоянный Address нашей Web страницы.  
static byte myip[] = {                                                                                                                                                                                                                   //                         _____                        *                   ___    *  _____                                  
  192,168,1,222 };                                                                                                                                                                                                                       //          /\    |       |       \  /  \            /  |  |\   |  |\   |  |   \   |    |                  
                                                                                                                                                                                                                                         //         /  \   |       |_____   \/    \    /\    /   |  | \  |  | \  |  |    \  |    |              
// Буфер, чем больше данных на Web странице, тем больше понадобится значения буфера.                                                                                                                                                     //        /----\  |       |        /\     \  /  \  /    |  |  \ |  |  \ |  |     ) |    |  
byte Ethernet::buffer[2000];                                                                                                                                                                                                             //       /      \ |_____| |_____  /  \     \/    \/     |  |   \|  |   \|  |____/  |    |                                                     
BufferFiller bfill;                                                                                                                                                                                                                                    


// Массив для фиксации изменений.
byte PinStatus[] = {
  1,2,3,4,5,6,7,8,9,10,11,12};
//-------------

const char http_OK[] PROGMEM =
"HTTP/1.0 200 OK\r\n"
"Content-Type: text/html\r\n"
"Pragma: no-cache\r\n\r\n";

const char http_Found[] PROGMEM =
"HTTP/1.0 302 Found\r\n"
"Location: /\r\n\r\n";

const char http_Unauthorized[] PROGMEM =
"HTTP/1.0 401 Unauthorized\r\n"
"Content-Type: text/html\r\n\r\n"
"<h1>401 Unauthorized</h1>";
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



// include the library code:
#include <LiquidCrystal.h>

#include <SPI.h>

#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 46
#define RST_PIN         48          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above
int k;

LiquidCrystal lcd(12, 8, 5, 4, 3, 2);
const int RedLed = 35;
const int BlueLed = 36;
const int buzzer = 28;
int chk;
const int pinStreetSensor = A4;
const int pinStreetLight = 7;
int sensorValue = 0;
//int RECV_PIN = A1;
int TKD2 = A1;
int insideLightValue = 0; 
int securityValue = 0;
//создаём объект ик приёмника
//IRrecv irrecv(RECV_PIN);
unsigned long times;
byte l;
#include <SoftwareSerial.h>
SoftwareSerial softSerial(10, 11); // RX, TX
int light = 1;
int climat = 0;
int secur = 0;
int d = 0; 
int tem;
int hum;
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void homePage()
{
  bfill.emit_p(PSTR("$F"
    "<title>Smart House</title>" 
    "ArduinoPIN 1: <a href=\"?ArduinoPIN1=$F\">$F</a><br />"
    "ArduinoPIN 2: <a href=\"?ArduinoPIN2=$F\">$F</a><br />"  
    "ArduinoPIN 3: <a href=\"?ArduinoPIN3=$F\">$F</a><br />"
    "ArduinoPIN 4: <a href=\"?ArduinoPIN4=$F\">$F</a><br />"
    "ArduinoPIN 5: <a href=\"?ArduinoPIN5=$F\">$F</a><br />"
    "ArduinoPIN 6: <a href=\"?ArduinoPIN6=$F\">$F</a><br />"
    "ArduinoPIN 7: <a href=\"?ArduinoPIN7=$F\">$F</a><br />"   
    "ArduinoPIN 8: <a href=\"?ArduinoPIN8=$F\">$F</a><br />"
    "ArduinoPIN 9: <a href=\"?ArduinoPIN9=$F\">$F</a><br />"
    "ArduinoPIN 10: <a href=\"?ArduinoPIN10=$F\">$F</a><br />"
    "ArduinoPIN 11: <a href=\"?ArduinoPIN11=$F\">$F</a><br />"
    "ArduinoPIN 12: <a href=\"?ArduinoPIN12=$F\">$F</a>"),   

  http_OK,
  PinStatus[1]?PSTR("off"):PSTR("on"),
  PinStatus[1]?PSTR("<font color=\"green\"><b>SecurityOn</b></font>"):PSTR("<font color=\"red\">SecurityOf</font>"),
  PinStatus[2]?PSTR("off"):PSTR("on"),
  PinStatus[2]?PSTR("<font color=\"green\"><b>SecChekerOn</b></font>"):PSTR("<font color=\"red\">SecChekerOf</font>"),
  PinStatus[3]?PSTR("off"):PSTR("on"),
  PinStatus[3]?PSTR("<font color=\"green\"><b>doorOPEN</b></font>"):PSTR("<font color=\"red\">doorCLOS</font>"),
  PinStatus[4]?PSTR("off"):PSTR("on"),
  PinStatus[4]?PSTR("<font color=\"green\"><b>HomeOU</b></font>"):PSTR("<font color=\"red\">HomeIN</font>"),
  PinStatus[5]?PSTR("off"):PSTR("on"),
  PinStatus[5]?PSTR("<font color=\"green\"><b>OutsideOF</b></font>"):PSTR("<font color=\"red\">OutsideON</font>"),
  PinStatus[6]?PSTR("off"):PSTR("on"),
  PinStatus[6]?PSTR("<font color=\"green\"><b>LampGOn</b></font>"):PSTR("<font color=\"red\">LampGOf</font>"), 
  PinStatus[7]?PSTR("off"):PSTR("on"),
  PinStatus[7]?PSTR("<font color=\"green\"><b>LampKOn</b></font>"):PSTR("<font color=\"red\">LampKOf</font>"), 
  PinStatus[8]?PSTR("off"):PSTR("on"),
  PinStatus[8]?PSTR("<font color=\"green\"><b>ClimatOn</b></font>"):PSTR("<font color=\"red\">ClimatOf</font>"),
  PinStatus[9]?PSTR("off"):PSTR("on"),
  PinStatus[9]?PSTR("<font color=\"green\"><b>SenChekerOn</b></font>"):PSTR("<font color=\"red\">SenChekerOf</font>"),
  PinStatus[10]?PSTR("off"):PSTR("on"),
  PinStatus[10]?PSTR("<font color=\"green\"><b>LampOOn</b></font>"):PSTR("<font color=\"red\">LampOOf</font>"),
  PinStatus[11]?PSTR("off"):PSTR("on"),
  PinStatus[11]?PSTR("<font color=\"green\"><b>GasChekerOn</b></font>"):PSTR("<font color=\"red\">GasChekerOf</font>"),
  PinStatus[12]?PSTR("off"):PSTR("on"),
  PinStatus[12]?PSTR("<font color=\"green\"><b>WatChekerOn</b></font>"):PSTR("<font color=\"red\">WatChekerOf</font>"));

bfill.emit_p(PSTR(
  "<meta http-equiv='refresh' content='60'/>" // Авто обновление Web страницы клиента, каждые 2 секунды.
  "<h1>Temperature$D"": Humidity$D</h1>"),tem, hum);  // h1 размер шрифта.
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void WebServer()
{

  delay(1); // Дёргаем микроконтроллер.

  word len = ether.packetReceive();   // check for ethernet packet / проверить ethernet пакеты.                         //                    _____   ___
  word pos = ether.packetLoop(len);   // check for tcp packet / проверить TCP пакеты.                                   //   \            /  |       |   \
                                                                                                                        //    \    /\    /   |_____  |____|
                                                                                                                        //     \  /  \  /    |       |     \
// Читаем один символ из буфера программного последовательного порта и сохраняем его переменную com                     //      \/    \/     |_____  |_____/
                                                                                                                                 

    
    
 
  
  
  if (pos) {
    bfill = ether.tcpOffset();
    char *data = (char *) Ethernet::buffer + pos;
    if (strncmp("GET /", data, 5) != 0) {
      bfill.emit_p(http_Unauthorized);
    }
    else {

      data += 5;
      if (data[0] == ' ') {       
        homePage(); // Return home page Если обнаружено изменения на станице, запускаем функцию.
        
      }

      // "16" = количество символов "?ArduinoPIN1=on ".
      else if (strncmp("?ArduinoPIN1=on ", data, 16) == 0) {
        PinStatus[1] = true; 
        secur = 1;       
        softSerial.write('s');
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN2=on ", data, 16) == 0) {
        PinStatus[2] = true;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN3=on ", data, 16) == 0) {
        PinStatus[3] = true;        
        softSerial.write('q');
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN4=on ", data, 16) == 0) {
        PinStatus[4] = true;        
        k = 1;
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN5=on ", data, 16) == 0) {
        PinStatus[5] = true;        
        //light = 0;
        digitalWrite(pinStreetLight, LOW);
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN6=on ", data, 16) == 0) {
        PinStatus[6] = true;        
        digitalWrite(13,HIGH);
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN7=on ", data, 16) == 0) {
        PinStatus[7] = true;        
        digitalWrite(6,HIGH);
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN8=on ", data, 16) == 0) {
        PinStatus[8] = true;        
        climat = 1;
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN9=on ", data, 16) == 0) {
        PinStatus[9] = true;        
        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN10=on ", data, 16) == 0) {
        PinStatus[10] = true;        
        digitalWrite(pinStreetLight, HIGH);
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN11=on ", data, 16) == 0) {
        PinStatus[11] = true;        
        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN12=on ", data, 16) == 0) {
        PinStatus[12] = true;        
        
        bfill.emit_p(http_Found);
      }
      //------------------------------------------------------  


      else if (strncmp("?ArduinoPIN1=off ", data, 17) == 0) {
        PinStatus[1] = false;        
        secur = 0;
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN2=off ", data, 17) == 0) {
        PinStatus[2] = false;        
        softSerial.write('y');
        securityValue = 0;
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN3=off ", data, 17) == 0) {
        PinStatus[3] = false;        
        softSerial.write('a');
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN4=off ", data, 17) == 0) {
        PinStatus[4] = false;        
        k = 0;
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN5=off ", data, 17) == 0) {
        PinStatus[5] = false;        
        //light = 1;
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN6=off ", data, 17) == 0) {
        PinStatus[6] = false;        
        digitalWrite(13,LOW);
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN7=off ", data, 17) == 0) {
        PinStatus[7] = false;        
        digitalWrite(6,LOW);
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN8=off ", data, 17) == 0) {
        PinStatus[8] = false;        
        climat = 0;
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN9=off ", data, 17) == 0) {
        PinStatus[9] = false; 
        sensorValue = 0;      
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN10=off ", data, 17) == 0) {
        PinStatus[10] = false;        
        digitalWrite(pinStreetLight, LOW);
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN11=off ", data, 17) == 0) {
        PinStatus[11] = false; 
        sensorValue = 0;      
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN12=off ", data, 17) == 0) {
        PinStatus[12] = false; 
        sensorValue = 0;      
        bfill.emit_p(http_Found);
      }

      //---------------------------


      else {
        // Page not found
        bfill.emit_p(http_Unauthorized);
      }
    }
    ether.httpServerReply(bfill.position());    // send http response
  }

}
void setup() {
  softSerial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
 // pinMode (pinStreetLight, OUTPUT);
  pinMode (RedLed, OUTPUT);
  pinMode (BlueLed, OUTPUT);
  pinMode (buzzer, OUTPUT);
  
  
 // irrecv.enableIRIn(); 
  
  SPI.begin();      // Init SPI bus
  
  k = 0;
  l = true;
  light = 1;
climat = 0;
secur = 0;
  Serial.begin(9600);
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(13,LOW);
  digitalWrite(6,LOW);
  
//----------------------------------------------------------------------------------------------
// По умолчанию в Библиотеке "ethercard" (CS-pin) = № 8.
  // if (ether.begin(sizeof Ethernet::buffer, mymac) == 0).
  // and change it to: Меняем (CS-pin) на 10.
  // if (ether.begin(sizeof Ethernet::buffer, mymac, 10) == 0).
  
  if (ether.begin(sizeof Ethernet::buffer, mymac,53) == 0);
  
  if (!ether.dhcpSetup()); 

  // Выводим в Serial монитор IP адрес который нам автоматический присвоил наш Router. 
  // Динамический IP адрес, это не удобно, периодический наш IP адрес будет меняться. 
  // Нам придётся каждый раз узнавать кой адрес у нашей страницы.
  ether.printIp("My Router IP: ", ether.myip); // Выводим в Serial монитор IP адрес который нам присвоил Router. 

  // Здесь мы подменяем наш динамический IP на статический / постоянный IP Address нашей Web страницы.
  // Теперь не важно какой IP адрес присвоит нам Router, автоматический будем менять его, например на "192.168.1.222". 
  ether.staticSetup(myip);

  ether.printIp("My SET IP: ", ether.myip); // Выводим в Serial монитор статический IP адрес. 
  //-----

  for (int i = 1; i <= 12; i++)PinStatus[i]=false;
  

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop()
{
  
  if ((k == 1)){
    //control();
    digitalWrite(30,LOW);
    digitalWrite(31,LOW);                                                                      
    Serial.println(light);
  if (PinStatus[5] == false){                                                                                
    streetLight();}                                                                     //               __       __      ___
   // RFID();                                                                           //    |        /    \   /    \   |    \
   gasSensor ();                                                                        //    |       |      | |      |  |____/ 
    water();                                                                            //    |       |      | |      |  |
    //IR();                                                                             //    |_____|  \____/   \____/   |
    if (secur == 1) security();
    chk = DHT.read(DHT11_PIN); 
    tem = DHT.temperature;
    hum = DHT.humidity;
    WebServer();
  //climat
    if (climat == 1){
    if (DHT.temperature >=25)
  {
    digitalWrite (BlueLed, HIGH);
  }
  else
  {
    digitalWrite (BlueLed, LOW);
  }
  if (DHT.temperature <=21)
  {
    digitalWrite (RedLed, HIGH); 
  }
  else
  {
    digitalWrite (RedLed, LOW);
  }
    }
    else digitalWrite (BlueLed, LOW);
    
  }
  
  if (k == 0)
  {
    
    WebServer();
    control();
    if (PinStatus[5] == false){
    streetLight();}
    gasSensor ();
    water();
//    IR();
    if (secur == 1) security();
    //RFID();
    // start working...
    
  // read without samples.
  chk = DHT.read(DHT11_PIN); 
   tem = DHT.temperature;
   hum = DHT.humidity;
   
   
   
  //climat
    if (climat == 1){
    if (DHT.temperature >=25)
  {
    digitalWrite (BlueLed, HIGH);
  }
  else
  {
    digitalWrite (BlueLed, LOW);
  }
  if (DHT.temperature <=21)
  {
    digitalWrite (RedLed, HIGH); 
  }
  else
  {
    digitalWrite (RedLed, LOW);
  }
    }
    else digitalWrite (BlueLed, LOW);
  //
   digitalWrite(30,HIGH); 
    digitalWrite(31,HIGH);
   if ( l == true) { lcd.setCursor(0, 0);
    lcd.print("Temperature: "); lcd.print(DHT.temperature); lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print("Humidity:    "); lcd.print(DHT.humidity); lcd.print("% ");  l = false;
   }
   times = millis();
  
   if ((times % 1000) == 0){
   lcd.setCursor(0, 0);
    lcd.print("Temperature: "); lcd.print(DHT.temperature); lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print("Humidity:    "); lcd.print(DHT.humidity); lcd.print("% ");
   }
  
 
}
}

void warning()
{
     while (sensorValue == 1){
     digitalWrite(buzzer, HIGH);
     
     lcd.setCursor(0,0);
     lcd.print ("  ATTENTION!!!  ");
     lcd.setCursor(0,1);
     lcd.print("   DANGER!!!    ");
     control();
     WebServer();
     l = true;
     }
     digitalWrite(buzzer, LOW);
     PinStatus[9] = false;
     PinStatus[11] = false;
     PinStatus[12] = false;
     
}

void gasSensor()
{
  int val;
  val = analogRead(0);
  //Serial.println(val);
  if (val >= 1000)
  {
    PinStatus[11] = true; 
    sensorValue = 1;
    warning();
    
  }
  else 
  {
    digitalWrite(buzzer, LOW);
  }
  int flame = analogRead(A3);
  //Serial.println(flame);
  if (flame >= 800)
  {
    PinStatus[9] = true;
    sensorValue = 1;
    warning();
  }
  else 
  {
    digitalWrite(buzzer, LOW);
  }
  
}  




void streetLight()
{
  int StreetSensor;
  StreetSensor = analogRead(pinStreetSensor);
  Serial.println(StreetSensor);
  if (StreetSensor >=801)
  {
    digitalWrite(pinStreetLight, HIGH);
  }
  else
  {
    digitalWrite(pinStreetLight, LOW);
  }
}

/*void RFID()
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
        
        myservo.write(90);
        lcd.setCursor(0,0);
        lcd.print ("    DOOR        ");
        lcd.setCursor(0,1);
        lcd.print("   OPEN!        ");
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
        myservo.write(180);
        lcd.setCursor(0,0);
        lcd.print ("    DOOR        ");
        lcd.setCursor(0,1);
        lcd.print("   CLOSED!      ");
        delay(1000);
        
  
  }
}*/
/*
void IR()
{
  decode_results results;
 //Если ик команда принята и успешно декодирована - 
 //выводим полученный код в сириал монитор
 if (irrecv.decode(&results)) {
  //1
  if (results.value == 16738455)
  {
    insideLightValue = 1;
    irrecv.resume();
  }
 
  //2
 if ((results.value == 16750695))
 {
    securityValue = 1;
    irrecv.resume();
 }
}
}
*/
void security()
{
   
    while (securityValue == 1){
      
       
      
      lcd.setCursor(0,0);
        lcd.print ("  Somebody is   ");
        lcd.setCursor(0,1);
        lcd.print("   in this area  ");
        control();
        WebServer();
        l = true;
        
        }
   
   
}


void DoorOP()
{
        
        lcd.setCursor(0,0);
        lcd.print ("    DOOR        ");
        lcd.setCursor(0,1);
        lcd.print("   OPEN!       ");
        WebServer();
        l = true;
        delay(1000);
}
void DoorCL()
{
        lcd.setCursor(0,0);
        lcd.print ("    DOOR        ");
        lcd.setCursor(0,1);
        lcd.print("   CLOSED!      ");
        WebServer();
        l = true;
        delay(1000);
}
void water()
{
  int waterSensor = analogRead(5);
  Serial.println(waterSensor);
  if (waterSensor >= 800) 
  {
    PinStatus[12] = true;
    sensorValue = 1;
    warning();
    
  }
  else   
  {
    digitalWrite(buzzer,LOW);
  }
}
void control()
{
  if (softSerial.available()){
      int com = softSerial.read();
    if (com == 'c') climat = 1;
    
    else if (com == 'd') climat = 0;

    else if (com == 'g') digitalWrite(13,HIGH);

    else if (com == 'v') digitalWrite(13,LOW);

    else if (com == 'k') digitalWrite(6,HIGH);

    else if (com == 'm') digitalWrite(6,LOW);

    else if (com == 'q') {DoorOP(); d = 1;  PinStatus[3] = true;}

    else if (com == 'a') {DoorCL(); d = 0; PinStatus[3] = false;}

    else if (com == 'o') k = 1;

    else if (com == 'i') k = 0;

    else if (com == 's') secur = 1;

    else if (com == 'x') secur = 0;

    else if (com == 'y') securityValue = 0;

    else if (com == 'p') sensorValue = 0;
        
    //else if (com == 'h') light = 1;

    //else if (com == 'b') light = 0;

    else if (com == '[') digitalWrite(pinStreetLight, HIGH);

    else if (com == ']') digitalWrite(pinStreetLight, LOW);
    
    else if (com == 't') {PinStatus[2] = true; securityValue = 1;}

    else if (com == 'l') PinStatus[9] = true;


}
}

