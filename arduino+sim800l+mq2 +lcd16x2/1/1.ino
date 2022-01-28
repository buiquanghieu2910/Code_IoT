#include <Sim800l.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//............................................................................
#define MQ2 A2
#define LED1 12
#define LED2 11
#define SPEAK 10
//............................................................................
Sim800l Sim800l;
LiquidCrystal_I2C lcd(0x27, 16, 2);

char* SDT = "0395962002";
String textSms, numberSms;
uint8_t index1;
bool errorSms, errorCall, sended = 0, called = 0;
int val;
int range = 20;
//............................................................................
void read_MQ2()
{
  val = analogRead(MQ2) / 1023.0 * 100 ;
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
void lcd_Gas(int val)
{
  float gasPercent = val;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Gas: ");
  lcd.print(gasPercent);
  lcd.print('%');
}
//............................................................................
void setup()
{
  Serial.begin(9600);
  pinMode(SPEAK, OUTPUT);
  pinMode(MQ2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  digitalWrite(LED1, 0);

  Serial.println("OK");
  Sim800l.begin();
  Sim800l.delAllSms();
  Serial.println("OK");

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  Serial.println("OK");
}

void loop()
{
  val = analogRead(A2) / 1023.0 * 100;
  Serial.println(val);
  if (val > 20)
  {
    digitalWrite(10, HIGH);
    //digitalWrite(5,HIGH);
  }

  if (val < 20)
  {
    digitalWrite(10, LOW);
    //digitalWrite(5,LOW);
  }

  read_MQ2();
  lcd_Gas(val);
  Serial.println(val);

  if (val > range && sended == 0 && called == 0 )
  {
    errorSms = Sim800l.sendSms(SDT, "Co khi gas");
    Sim800l.callNumber(SDT);
    if (!errorSms)
      Serial.println("Send SMS failed");
    else
    {
      Serial.println("Call and SMS Success !");
      called = 1;
      sended = 1;
    }
  }
  Serial.println("OK");
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
        if (!errorSms)
          Serial.println("Send SMS failed");
        Serial.println("TAT QUAT");
      }
      else if (textSms.indexOf("TAT QUAT") != -1)
      {
        toff();
        errorSms = Sim800l.sendSms(SDT, "Quat da tat");
        if (!errorSms)
          Serial.println("Send SMS failed");
        called = 0;
        sended = 0;
        Serial.println("LED OFF");
      }
      else if (textSms.indexOf("BAT NUOC") != -1)
      {
        non();
        errorSms = Sim800l.sendSms(SDT, "Nuoc da bat");
        if (!errorSms)
          Serial.println("Send SMS failed");
        called = 0;
        sended = 0;
        Serial.println("LED OFF");
      }
      else if (textSms.indexOf("TAT NUOC") != -1)
      {
        noff();
        errorSms = Sim800l.sendSms(SDT, "Nuoc da tat ");
        if (!errorSms)
          Serial.println("Send SMS failed");
        called = 0;
        sended = 0;
        Serial.println("LED OFF");
      }
      Sim800l.delAllSms();
    }
  }
}
