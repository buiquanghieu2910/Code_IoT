#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
// You should get Auth Token in the Blynk App.

// Go to the Project Settings (nut icon).

char auth[] = "jdKJuuHQ9-vVUBTwuhMr6Mj1bEpv1tkF";

// Your WiFi credentials.

// Set password to “” for open networks.
char ssid[] = "SAI LAM CUA ANH";
char pass[] = "0964060702";
int n;
void setup()

{

// Debug console

Serial.begin(9600);

Blynk.begin(auth, ssid, pass);

Blynk.syncAll(); //This will sync the last state of your device
pinMode(16,OUTPUT);
  pinMode(5,OUTPUT);
  timer.setInterval(1000L, sendUptime);
}
void sendUptime()
{
  Blynk.virtualWrite(V1, n);
}
void loop()

{

Blynk.run();
timer.run();
  
  n=analogRead(A0)/1023.0*100;
  Serial.println(n);
  
  if(n>20)
  {
     digitalWrite(16,HIGH);
    //digitalWrite(5,HIGH);   
  }
  
  if(n<20)
  {
      digitalWrite(16,LOW);
      //digitalWrite(5,LOW);
  }

}
