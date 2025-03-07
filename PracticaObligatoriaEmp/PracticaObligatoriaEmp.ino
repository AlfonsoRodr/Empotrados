/**
* @file PracticaObligatoriaEmp.ino
* @author Alfonso Rodríguez Gutt, Raúl Sánchez Benitez, Andrés Muñoz Muñoz, Héctor González Viñas.
* @brief Main program to control the buzzer with an LDR. 
* This program reads the values ​​of the LDR connected to pin A0 and, depending on the luminosity detected, plays a melody for a certain time on the buzzer.
*/

// Frecuencies for each music note (Hz)
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

#define UP_DURATION 10000 // Duration of the "Up" melody in milliseconds.
#define DOWN_DURATION 5000 // Duration of the "Down" melody in milliseconds.

int LDR = A0;  // Analogical PIN where the LDR is connected.
int buzzer = 8; // Digital PIN where the buzzer is connected.
int treshold = 0; 
int readValue = 0;
int button = 2;
int buttonState = 0; // Digital PIN where the button is connected.
int previousButtonState = 0;
int lastMelodyReproduced = 0; // When set to 1, the last melody played is the one that played when the threshold was exceeded. Otherwise, it will be 0.

// These are the arrays that will store the notes that each melody will have.
int luminosityUpMelody[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4};
int luminosityDownMelody[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};

// These are the arrays that will store the duration for each note for the corresponding melodies.
int melodyUpDuration[] = {1000, 1000, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 1000, 2000};
int melodyDownDuration[] = {500, 500, 500, 500, 500, 500, 500, 1700};

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  randomSeed(analogRead(0));  // Initialize the random seed.
  pinMode(button, INPUT_PULLUP);
  treshold = random(300, 700);  
  Serial.print("Umbral generado: ");
  Serial.println(treshold);
}

/**
* @brief This method checks if the specified time duration has been exceeded.
* @param startTime The initial time (millis()) at the start of the process.
* @param elapsedTime The elapsed time since the startTime.
* @param duration The total time duration to check against.
* @return true if the time has been exceeded, false otherwise.
*/
bool timeExceeded(unsigned long startTime, unsigned long elapsedTime, unsigned long duration) {
  elapsedTime = millis() - startTime;
  return elapsedTime >= duration;
}
/**
* @brief This method produces a triple beep when the button is pressed.
*/
void buttonPressed() {
  for (int i = 0; i < 3; i++) {
    tone(buzzer, 1000, 200);
    delay(500);
  }
}

/**
* @brief This method will activate the buzzer with a melody, ensuring the total time does not exceed the given duration.
* @param melody is the array where the notes of the melody are stored.
* @param durations is the array where the duration of each note are stored.
* @param length  is the size of the melody array.
* @param totalTime is the time limit. This value will depend on whether the threshold value has been exceeded or not.
*/
void activateBuzzer(int* melody, int* durations, int length, int totalTime) {
  unsigned long startTime = millis();
  unsigned long elapsedTime = 0;
  unsigned long remainingTime = 0;

  for (int i = 0; i < length; i++) {
    if (timeExceeded(startTime, elapsedTime, totalTime)) {
      break;
    }
    tone(buzzer, melody[i], durations[i]); // Play the melody.
    remainingTime = totalTime - elapsedTime;
    if (durations[i] > remainingTime) { // If the duration of a note i is higher than the remaining time, then it will wait for the remaining time.
      delay(remainingTime);
    } 
    else { // If not, it will continue normally (wait for the note to finish).
      delay(durations[i]);
    }
  }
  noTone(buzzer);
}

/**
* @brief This method will reproduced the last melody played two times when the button is not pressed, with a delay of 5 seconds between each other.
* @param melody is the array where the notes of the melody are stored.
* @param durations is the array where the duration of each note are stored.
* @param size is the length of the melody array.
* @param timeDuration is the time limit for an specific scenario. 
* In other words, this parameter is what differentiates one melody from another, thus allowing the playback of the last melody played.
*/
void buttonNotPressed(int *melody, int *durations, int size, unsigned long timeDuration) {
  for (int i = 0; i < 2; i++) {
    activateBuzzer(melody, durations, size, timeDuration);
    delay(5000);
  }
}

/**
* @note The button is configured with an internal pull-up resistor, meaning that when it is pressed, the pin will read LOW.
*/
void loop() {
  readValue = analogRead(LDR); // Luminosity value obtained from the LDR.
  buttonState = digitalRead(button); // Read the state of the button.
  Serial.print("Valor leído: ");
  Serial.println(readValue);

  if (buttonState != previousButtonState) {
    previousButtonState = buttonState;
    if (buttonState == LOW) { // If the button is pressed --> LOW (pull-up button)
      Serial.println("Botón presionado");
      buttonPressed();
      if (readValue >= treshold) {
        Serial.println("Sonando Buzzer por 10 segundos");
        activateBuzzer(luminosityUpMelody, melodyUpDuration, 14, UP_DURATION);
        lastMelodyReproduced = 1;
      } 
      else {
        Serial.println("Sonando Buzzer por 5 segundos");
        activateBuzzer(luminosityDownMelody, melodyDownDuration, 8 , DOWN_DURATION);
        lastMelodyReproduced = 0;
      }
    }
    else {
      Serial.println("Botón no presionado");
      // When the button is not pressed, repeat the last melody played
      if (lastMelodyReproduced == 1) {
        buttonNotPressed(luminosityUpMelody, melodyUpDuration, 14, UP_DURATION); // UP melody.
      }
      else {
        buttonNotPressed(luminosityDownMelody, melodyDownDuration, 8 , DOWN_DURATION); // DOWN melody.
      }
    }
  }
  noTone(buzzer);  // Stop any sound that might still be playing.
  delay(1000);  // Wait 1 second.
}