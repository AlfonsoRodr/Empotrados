/**
 * @file PasswordResult.ino
 * @brief Se verán los resultados de la contraseña (acierto o fallo) en los LEDs, LCD y Buzzer (TRADUCIR).
 * @author Héctor González.
 * @author Raúl Sánchez.
 * @date 14/03/2025.
 */

#include <LiquidCrystal_I2C.h>
/*#include <Keypad.h>
#include <Wire.h>*/

#define BUZZER 10
#define LED 11


LiquidCrystal_I2C lcd(0x3f,16,2); // This will be the direction for the I2C interface (it is fixed).
//user chances to key correct psw
int triesLeft=3;
bool wrongIntroducedPsw=1;

/*
// Dimensions of the keypad
const byte FILAS = 4;
const byte COLUMNAS = 4;

// Setting the keys
char teclas[FILAS][COLUMNAS] = { 
  {'R', 'A', 'U', 'L'},
  {'P', 'U', 'T', 'E'},
  {'O', '1', '9', 'C'},
  {'*', '0', '#', ' '}
};

// Conections
byte pinesFilas[FILAS] = {9, 8, 7, 6};    
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2}; 

// Keypad initializer.
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);*/

void setup() {
  lcd.init(); // LCD is initialize.
  lcd.backlight(); // Turning on retroilumination. Because of this, the screen wont be turning on.
  lcd.clear(); // Clear the screen (just in case).
  pinMode(BUZZER,OUTPUT);
  pinMode(LED,OUTPUT);
}

/**
* @brief This method will manage the resutls when the correct password is entered.
* @author Raúl Sánchez.
*/
void correctPassword() {
  // TODO: RAÚL LO IMPLEMENTARÁ.
  lcd.setCursor(0,0);
  lcd.print("Correct password!!");
}

/**
* @brief This method will manage the results when a wrong password is entered.
* @author Héctor González.
*/
void wrongPsw(){
  triesLeft--;
  lcd.setCursor(0,0); // The parameters are (colum, row). It will posicionated on the screen the message we want to show. (0, 0) means first column and first row
  lcd.print("Wrong password ");  // This will be the message.
  Serial.println("Wrong password introduced");
  lcd.setCursor (0,1); // Same thing.
  lcd.print("tries left: "); 
  lcd.print(triesLeft);
  delay(1000);
}

void loop() {
  if(triesLeft > 0 && wrongIntroducedPsw){
    lcd.print("Introduce psw:");
    
    // El while de abajo se pone cuando ya haya botoncitos y el  delay se quita siuuu
    //while (!teclado.getKey()); // The welcome message will appear until a key is pressed.
    delay(5000);

    wrongPsw();
    tone(BUZZER,500);
    delay(500);
    noTone(BUZZER);
    lcd.clear();
    //delay(5000);

  }else if(triesLeft==0 && wrongIntroducedPsw){
    //bloquear todo
    lcd.setCursor(0,0); // The parameters are (colum, row). It will posicionated on the screen the message we want to show. (0, 0) means first column and first row
    lcd.print("No tries left");
    while(1){
      tone(BUZZER,1000);
      delay(300);
      tone(BUZZER,1500);
      delay(300);
    }
  }else{
    //Contraseña Correcta
    correctPassword();
    digitalWrite(LED, HIGH); // Enciende el LED si la contraseña es correcta.
    tone(BUZZER,100);
    delay(300);
    tone(BUZZER,100);
    noTone(BUZZER);
    delay(1000);
    lcd.clear();

  }
}