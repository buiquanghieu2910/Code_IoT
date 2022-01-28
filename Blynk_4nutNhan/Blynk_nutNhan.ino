
#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
char auth[] = "J23LNMxQo83_h7Wj_faWpVnYF7OLNrUH";  ///////////////// nhập mã auth blynk
char ssid[] = "BUI QUANG HIEU";              //////nhập tên wifi
char pass[] = "0395962002";              ////////////nhập pass wifi 
int virtualPin1;
int flag1=0;
int virtualPin2;
int flag2=0;
int virtualPin3;
int flag3=0;
int virtualPin4;
int flag4=0;


int buttonState1 = LOW;       // trạng thái chân gắn nút nhấn
int lastButtonState1 = LOW;   // trạng thái trước đó của nút
int buttonState2 = LOW;
int lastButtonState2 =LOW;
int buttonState3 = LOW;
int lastButtonState3 =LOW;
int buttonState4 = LOW;
int lastButtonState4 =LOW;

// biến thời gian cần giá trị lớn (theo ms)
unsigned long lastDebounceTime1 = 0;  // lưu thời gian trạng thái nút nhấn trước
unsigned long debounceDelay1 = 20;    // thời gian khử nhiễu
unsigned long lastDebounceTime2 = 0;  // lưu thời gian trạng thái nút nhấn trước
unsigned long debounceDelay2 = 20;    // thời gian khử nhiễu
unsigned long lastDebounceTime3 = 0;  // lưu thời gian trạng thái nút nhấn trước
unsigned long debounceDelay3 = 20;    // thời gian khử nhiễu
unsigned long lastDebounceTime4 = 0;  // lưu thời gian trạng thái nút nhấn trước
unsigned long debounceDelay4 = 20;    // thời gian khử nhiễu
// WidgetLED led1(V1);

//Gửi dữ liệu trạng thái Button từ Blynk về Nodemcu
BLYNK_WRITE(V5)
{
  virtualPin1 = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V0 Slider value is: ");
  Serial.println(virtualPin1);
  flag1 = 1;
}

BLYNK_WRITE(V6)
{
  virtualPin2 = param.asInt(); 
  Serial.print("V0 Slider value is: ");
  Serial.println(virtualPin2);
  flag2 = 1;
}
BLYNK_WRITE(V7)
{
  virtualPin3 = param.asInt(); 
  Serial.print("V0 Slider value is: ");
  Serial.println(virtualPin3);
  flag3 = 1;
}
BLYNK_WRITE(V8)
{
  virtualPin4 = param.asInt(); 
  Serial.print("V0 Slider value is: ");
  Serial.println(virtualPin4);
  flag4 = 1;
}
//Đồng bộ lại trạng thái khi mất nguồn
BLYNK_CONNECTED(){
  Blynk.syncVirtual(V5);  
  Blynk.syncVirtual(V6);
  Blynk.syncVirtual(V7);
  Blynk.syncVirtual(V8);
  }

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
//  Blynk.virtualWrite(V5, h);
//  Blynk.virtualWrite(V6, t);
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk-server.com",8080);
  dht.begin();
  pinMode(16, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(14, OUTPUT);
  pinMode(1,INPUT);
  pinMode(12, OUTPUT);
  pinMode(3,INPUT);
  pinMode(13, OUTPUT);
  pinMode(2,INPUT);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
 //
  if(flag1 == 1){
  if(virtualPin1 == 0){
    digitalWrite(16, LOW);
    }
    else digitalWrite(16, HIGH);
  }

 int reading1 = digitalRead(0);
 int ledStatus1 = digitalRead(16);
 
 if (reading1 != lastButtonState1) {
    // lưu thời gian
    lastDebounceTime1 = millis();
  }
 if ((millis() - lastDebounceTime1) > debounceDelay1) {
    // nếu thời gian giữ trạng thái lớn hơn khoảng đã định:
    // nếu trạng thái đã đổi
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      // đổi trạng thái đèn theo nút nhấn
      if (buttonState1 == HIGH) {     

    if(ledStatus1 == 0){
      digitalWrite(16, HIGH);
      Blynk.virtualWrite(V5,1); //Ghi dữ liệu từ Nodemcu lên Blynk
      Blynk.notify("T1 đã được bật lên");
      //led1.off();
      }
      else {
      digitalWrite(16, LOW);
      Blynk.virtualWrite(V5,0); ////Ghi dữ liệu từ Nodemcu lên Blynk
      Blynk.notify("T1 đã được tắt");
     // led1.on();
      }
      }
    }
 }
      
  lastButtonState1 = digitalRead(0);
  flag1 = 0;

 //
   if(flag4 == 1){
  if(virtualPin4 == 0){
    digitalWrite(13, LOW);
    }
    else digitalWrite(13, HIGH);
  }


 int reading4 = digitalRead(2);
 int ledStatus4 = digitalRead(13);
 
 if (reading4 != lastButtonState4) {
    // lưu thời gian
    lastDebounceTime4 = millis();
  }
 if ((millis() - lastDebounceTime4) > debounceDelay4) {
    // nếu thời gian giữ trạng thái lớn hơn khoảng đã định:
    // nếu trạng thái đã đổi
    if (reading4 != buttonState4) {
      buttonState4 = reading4;

      // đổi trạng thái đèn theo nút nhấn
      if (buttonState4 == HIGH) {     
///////////////////////////////// //// / /hàm debouce sẽ nằm ở đây

    if(ledStatus4 == 0){
      digitalWrite(13, HIGH);
      Blynk.virtualWrite(V8,1); //Ghi dữ liệu từ Nodemcu lên Blynk
      Blynk.notify("T4 đã được bật lên");
      //led1.off();
      }
      else {
      digitalWrite(13, LOW);
      Blynk.virtualWrite(V8,0); ////Ghi dữ liệu từ Nodemcu lên Blynk
      Blynk.notify("T4 đã được tắt");
     // led1.on();
      }
      }
    }
 }
      
  lastButtonState4 = digitalRead(2);
  flag4 = 0;

 //
   if(flag2 == 1){
  if(virtualPin2 == 0){
    digitalWrite(14, LOW);
    }
    else digitalWrite(14, HIGH);
  }

///////////////////////////////////////////hàm debouce sẽ nằm ở đây

 int reading2 = digitalRead(1);
 int ledStatus2 = digitalRead(14);
 
 if (reading2 != lastButtonState2) {
    // lưu thời gian
    lastDebounceTime2 = millis();
  }
 if ((millis() - lastDebounceTime2) > debounceDelay2) {
    // nếu thời gian giữ trạng thái lớn hơn khoảng đã định:
    // nếu trạng thái đã đổi
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      // đổi trạng thái đèn theo nút nhấn
      if (buttonState2 == HIGH) {     
///////////////////////////////// //// / /hàm debouce sẽ nằm ở đây

    if(ledStatus2 == 0){
      digitalWrite(14, HIGH);
      Blynk.virtualWrite(V6,1); //Ghi dữ liệu từ Nodemcu lên Blynk
      Blynk.notify("T2 đã được bật lên");
      //led1.off();
      }
      else {
      digitalWrite(14, LOW);
      Blynk.virtualWrite(V6,0); ////Ghi dữ liệu từ Nodemcu lên Blynk
      Blynk.notify("T2 đã được tắt");
     // led1.on();
      }
      }
    }
 }
      
  lastButtonState2 = digitalRead(1);
  flag2 = 0;
//
   if(flag3 == 1){
  if(virtualPin3 == 0){
    digitalWrite(12, LOW);
    }
    else digitalWrite(12, HIGH);
  }

 int reading3 = digitalRead(3);
 int ledStatus3 = digitalRead(12);
 
 if (reading3 != lastButtonState3) {
    // lưu thời gian
    lastDebounceTime3 = millis();
  }
 if ((millis() - lastDebounceTime3) > debounceDelay3) {
    // nếu thời gian giữ trạng thái lớn hơn khoảng đã định:
    // nếu trạng thái đã đổi
    if (reading3 != buttonState3) {
      buttonState3 = reading3;

      // đổi trạng thái đèn theo nút nhấn
      if (buttonState3 == HIGH) {     

    if(ledStatus3 == 0){
      digitalWrite(12, HIGH);
      Blynk.virtualWrite(V7,1); //Ghi dữ liệu từ Nodemcu lên Blynk
      Blynk.notify("T3 đã được bật lên");
      //led1.off();
      }
      else {
      digitalWrite(12, LOW);
      Blynk.virtualWrite(V7,0); ////Ghi dữ liệu từ Nodemcu lên Blynk
      Blynk.notify("T3 đã được tắt");
     // led1.on();
      }
      }
    }
 }
      
  lastButtonState3 = digitalRead(3);
  flag3 = 0;
}
