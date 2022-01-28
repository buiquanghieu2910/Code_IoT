#include <Sim800l.h>
#include <SoftwareSerial.h>
//............................................................................
#define MQ2 A2
#define LED 13
//............................................................................
Sim800l Sim800l;
char sdt = "+84358324575";
String textSms, numberSms;
uint8_t index1;
bool error, called = 0;
int val;
int range = 500;
//............................................................................
void read_MQ2()
{
  val = analogRead(MQ2);
}
//............................................................................
void ton()
{
  digitalWrite(LED, 1);
}
//............................................................................
void toff()
{
  digitalWrite(LED, 0);
}
//............................................................................
void setup() {
  Serial.begin(9600);
  pinMode(MQ2, INPUT);
  pinMode(LED, OUTPUT);

  
  Sim800l.begin();
//  Sim800l.reset();
  Sim800l.delAllSms();
  Serial.println("ok");
}

void loop()
{
  read_MQ2();
  if(val > range && called == 0)
  {
    Sim800l.callNumber(sdt);
    called = 1;
  }
  textSms = Sim800l.readSms(1);
  if (textSms.indexOf("OK") != -1)
  {
    if (textSms.length() > 6)
    {
      numberSms = Sim800l.getNumberSms(1);
      textSms.toUpperCase();
      Serial.print(textSms);
      if (textSms.indexOf("TURN ON") != -1)
      {
        ton();
        bool a = Sim800l.sendSms(sdt, "Led is turn on");
      }
      else if (textSms.indexOf("TURN OFF") != -1)
      {
        toff();
        bool a = Sim800l.sendSms(sdt, "Led is turn off");
      }
      Sim800l.delAllSms();
    }
  }
}
