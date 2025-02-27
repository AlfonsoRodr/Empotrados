#include <LiquidCrystal_I2C.h>
/*
 Board I2C / TWI pins
Uno       =   A4 (SDA), A5 (SCL)
*/

/* This will be the code that manage the display of the LCD screen. In specific, this will show a message for an specific time, then dessapear it for 
another specific time, and then show it again. However, the configuration will be the same, the only thing that it will be needed to change is in the loop() section
*/
LiquidCrystal_I2C lcd(0x3f,16,2); // This will be the direction for the I2C interface (it is fixed).
void setup() {
  lcd.init(); // LCD is initialize
  lcd.backlight(); // Turning on retroilumination. Because of this, the screen wont be turning on
  lcd.clear(); // Clear the screen (just in case)
  lcd.setCursor(0,0); // The parameters are (colum, row). It will posicionated on the screen the message we want to show. (0, 0) means first column and first row
  lcd.print("Raul y Andres");  // This will be the message.
  lcd.setCursor (0,1); // Same thing
  lcd.print("Van a copular"); 
}

void loop() { 
  lcd.display(); // The screen will turn on.
  delay(500); // Timer
  lcd.noDisplay(); // The screen will turn off.
  delay(500);
}