#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.

// Go to the Project Settings (nut icon).

char auth[] = "RRiCdEuKhU-9sL-qPZklzdpJKi1-bNXe";

// Your WiFi credentials.

// Set password to “” for open networks.

char ssid[] = "BUI QUANG HIEU";

char pass[] = "0395962002";

void setup()

{

// Debug console

Serial.begin(9600);

Blynk.begin(auth, ssid, pass);

Blynk.syncAll(); //This will sync the last state of your device

}

void loop()

{

Blynk.run();

}
