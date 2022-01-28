#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
WidgetLED led1(V0);
char auth[] = "J23LNMxQo83_h7Wj_faWpVnYF7OLNrUH";        //Token cua blynk
char ssid[] = "HORSE_SOFTWARE";        //Ten wifi
char pass[] = "hsoftteam";         //Pass wifi

#define DHTPIN 2          // Pin ket noi voi DHT
#define DHTTYPE DHT11     // Su dung cam bien DHT11
DHT dht(DHTPIN, DHTTYPE); // Cau hinh chan DHT 
SimpleTimer timer;        // Su dung timer

//Ham gui du lieu
void sendSensor()
{
  if(led1.getValue()){
    led1.off();
  }
  else{
    led1.on();
  }
  float h = dht.readHumidity();     //Doc gia tri do am
  float t = dht.readTemperature();  //Doc gia tri nhiet do

  // Gan du lieu vao bien virtual de hien thi len blynk
  // Chi nen gan 10 bien tro xuong
  delay(10);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, t);
  // Luu y nen ban khong du energy thi co the bo qua v2 va v3
  Blynk.virtualWrite(V3, h);
  Blynk.virtualWrite(V4, t);
}
void setup() {
  Serial.begin(9600);                   // Mo Serial
//  Blynk.begin(auth, ssid, pass);  
  Blynk.begin(auth, ssid, pass, "blynk-server.com",8080); // Ket noi voi blynk
  Blynk.syncAll(); //This will sync the last state of your device
  dht.begin();                          // Khoi tao DHT
  timer.setInterval(1000L, sendSensor); //1s doc cam bien 1 lan

  }
void loop() {
  Blynk.run(); // Chay Blynk
  timer.run(); // Chay SimpleTimer
// Debug
//  Serial.print("Do am: ");
//  Serial.print(V0);
//  Serial.print(" %\t");
//  Serial.print("Nhiet do: ");
//  Serial.print(t);
//  Serial.println(" *C ");
  delay(2000);                // Doi chuyen doi.

}
