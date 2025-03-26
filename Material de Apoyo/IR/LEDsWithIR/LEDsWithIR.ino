#include <IRremote.h>

// This code will turn on and turn off a LED with the IR remote control
#define PIN_IR 2
#define LED 3  // LED Pin
#define BOTON_ENCENDER 0xFFA25D  // Code of the button (This code has to be changed for the one that it will be used)

bool estadoLED = false;  // Keep the state of the LED.

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    IrReceiver.begin(PIN_IR, ENABLE_LED_FEEDBACK);
}

void loop() {
    if (IrReceiver.decode()) {
        unsigned long codigo = IrReceiver.decodedIRData.decodedRawData;
        Serial.print("Código recibido: 0x");
        Serial.println(codigo, HEX);
        
        if (codigo == BOTON_ENCENDER) {
            estadoLED = !estadoLED;  // It changes the state of the LED.
            digitalWrite(LED, estadoLED ? HIGH : LOW);
            delay(300);
        }
        IrReceiver.resume();
    }
}