#include <Sim800l.h>
#include <SoftwareSerial.h>
//............................................................................
#define MQ2 A2
#define LED1 12
#define LED2 11
//............................................................................
Sim800l Sim800l;
char* SDT = "+84395962002";
String textSms, numberSms;
uint8_t index1;
bool errorSms, errorCall, sended = 0, called = 0;
int val;
int range = 1021;
//............................................................................
void read_MQ2()
{
  val = analogRead(MQ2);
}
//............................................................................
void ton()
{
  digitalWrite(LED1, 1);
}
//............................................................................
void toff()
{
  digitalWrite(LED1, 0);
}
//............................................................................
void non()
{
  digitalWrite(LED2, 1);
}
//............................................................................
void noff()
{
  digitalWrite(LED2, 0);
}
//............................................................................
void setup() {
  
//  Sim800l.begin();
//  Sim800l.callNumber(SDT);
  pinMode(A1, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(MQ2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  digitalWrite(LED1, 0);
Serial.begin(9600);
 Serial.println("OK a Hieu");
Sim800l.begin();
 
  
  
  //  Sim800l.reset();
  Sim800l.delAllSms();
  Serial.println("ok");
//    Sim800l.callNumber(SDT);
//Sim800l.sendSms(SDT, "Co khi gas");
//    Serial.println("Called");
}

void loop()
{
  if (digitalRead(A2) == 0)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
    
  read_MQ2();
  Serial.println(val);
  
  if (val > range && sended == 0 && called == 0 )
  {
    errorSms = Sim800l.sendSms(SDT, "Xe bi dat a Hieu oi !");
    Sim800l.callNumber(SDT);
    if(!errorSms)
      Serial.println("Send SMS failed");
    else
    {
      Serial.println("Call and SMS Success !");
      called = 1;
      sended = 1;
    } 
  }
  
  textSms = Sim800l.readSms(1);
  
  if (textSms.indexOf("OK") != -1)
  {
    if (textSms.length() > 6)
    {
      numberSms = Sim800l.getNumberSms(1);
      textSms.toUpperCase();
      Serial.print(textSms);
      if (textSms.indexOf("BAT QUAT") != -1)
      {
        ton();
        errorSms = Sim800l.sendSms(SDT, "Quat da bat");
        if(!errorSms)
          Serial.println("Send SMS failed");
        Serial.println("TAT QUAT");
      }
      else if (textSms.indexOf("TAT QUAT") != -1)
      {
        toff();
        errorSms = Sim800l.sendSms(SDT, "Quat da tat");
        if(!errorSms)
          Serial.println("Send SMS failed");
        called = 0;
        sended = 0;
        Serial.println("LED OFF");
      }
      else if (textSms.indexOf("BAT NUOC") != -1)
      {
        non();
        errorSms = Sim800l.sendSms(SDT, "Nuoc da bat");
        if(!errorSms)
          Serial.println("Send SMS failed");
        called = 0;
        sended = 0;
        Serial.println("LED OFF");
      }
      else if (textSms.indexOf("TAT NUOC") != -1)
      {
        noff();
        errorSms = Sim800l.sendSms(SDT, "Nuoc da tat ");
        if(!errorSms)
          Serial.println("Send SMS failed");
        called = 0;
        sended = 0;
        Serial.println("LED OFF");
      }
      Sim800l.delAllSms();
    }
  }
}
