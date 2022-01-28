//CHƯƠNG TRÌNH GÔI ĐIỆN ĐẾN ĐIỆN THOẠI DÙNG MODULE SIM 900 MINI VERSION
//NGƯỜI VIẾT HUỲNH MINH PHÚ
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); // CHÂN TX NỐI VỚI CHÂN 3, CHÂN RX NỐI VỚI CHÂN 4
#define  led  A1
int solan=0;
//Đọc các cb:
#define mq7_1 A4
#define mq7_2 A3
#define mq2 A2
int gtmq7_1,gtmq7_2,gtmq2;
void setup()
{
  pinMode(A5, INPUT_PULLUP);
  pinMode(mq7_1,INPUT);
  pinMode(mq7_2,INPUT);
  pinMode(mq2,INPUT);
  pinMode(led,OUTPUT);  
  Serial.begin(9600);
  mySerial.begin(9600);
    }
void loop()
{ 
  if(digitalRead(A5) == 0)
   digitalWrite(12, HIGH);
 else
   digitalWrite(12, LOW);
  gtmq7_1=analogRead(mq7_1);
  gtmq7_2=analogRead(mq7_2);
  gtmq2=analogRead(mq2);
  Serial.print("mq7_1   ");
  Serial.print("mq7_2   ");
  Serial.print("mq2");
  Serial.println();
  Serial.print(gtmq7_1);
  Serial.print("     ");
  Serial.print(gtmq7_2);
  Serial.print("     ");
  Serial.print(gtmq2);
  Serial.println();
  if(((gtmq7_1>200)||(gtmq7_2>200)||(gtmq2>200))&&(solan==0))
  {
    digitalWrite(led,HIGH);
     goidien();
  }
if((gtmq7_1<180)&&(gtmq7_2<180)&&(gtmq2<180))
{       
      digitalWrite(led,LOW);
      solan=0;
  }
}

void goidien()
{
  mySerial.println("ATD+84964060702;"); // GỌI ĐẾN SỐ
  Serial.println("dang goi");
   solan=1;
  delay(5000);            // CHỜ 15S
  mySerial.println();

   }
  
   
 
