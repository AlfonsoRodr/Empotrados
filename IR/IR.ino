#include <IRremote.h>

// This code main objetive is to obtain the code for each button in the remote control.
#define PIN_IR 2  // Connection Pin of the IR receiver.

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(PIN_IR, ENABLE_LED_FEEDBACK);  // The IR receiver is initialized.
}

void loop() {
    if (IrReceiver.decode()) {  // If the IR receiver receives a signal from the IR remote control then:
        Serial.print("Código recibido: 0x");
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);  // Show the receiving code in HEX format.
        IrReceiver.resume();  // Prepare the IR receiver for the next signal
    }
}