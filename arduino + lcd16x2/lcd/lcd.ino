#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
String intro = "   Cach Chay Chu Tren Man Hinh LCD Dung Arduino     ";
void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
//	lcd.backlight();
//	lcd.print("NGUYET LOVE KIEU");
// lcd.setCursor(0,1);
//  lcd.print("     ahihi =))");

//lcd.print("NGUYEN ANH DUNG");
// lcd.setCursor(0,1);
//  lcd.print("  BAC THAY C#");

for (int i=0; i<intro.length()-16; i++){

    for (int j=0; j<16; j++){

      lcd.setCursor(j,0);

      lcd.print(intro[i+j]);

    }

//    delay(500);

  }
  delay(500);
}

void loop()
{
	// Do nothing here...
}
