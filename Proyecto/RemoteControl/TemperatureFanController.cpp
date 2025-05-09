/**
 * @file TemperatureFanController.cpp
 * @author Alfonso Rodríguez.
 * @brief Implementation file for temperature and fan control using a DHT11 sensor.
 */

#include "TemperatureFanController.h"

// Create the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

bool manualOverride = false;
 
/**
 * @brief Initializes serial communication, the DHT sensor, and fan control pin.
 *
 * This function sets up the hardware required for temperature monitoring.
 * It begins the serial interface, initializes the DHT11 sensor, and configures
 * the fan control pin as an output, starting in the OFF state.
 */
void setupTemperatureFan() {
  Serial.begin(9600);
  dht.begin();
 
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW); // Ensure fan is off at startup
}

/**
 * @brief Checks if the given temperature exceeds the predefined threshold.
 *
 * This function compares the provided temperature with the threshold value (TEMPERATURE_TRESHOLD).
 * If the temperature is higher than the threshold, it returns true; otherwise, it returns false.
 *
 * @param temperature The current temperature value.
 * @return A boolean value indicating whether the temperature exceeds the threshold.
 */
bool exceededTreshold(float temperature) {
  return temperature > TEMPERATURE_TRESHOLD;
}

/**
 * @brief Controls the activation of the fan based on the current temperature.
 * This function checks if the current temperature exceeds the predefined threshold.
 * If it does, the fan is turned on, and a message is printed to the serial monitor.
 * If the temperature is below the threshold, the fan is turned off, and a message is printed to the serial monitor.
 * The fan's state is controlled via the FAN_PIN, and the fan's status is communicated via the serial monitor.
 *
 * @param temperature is the temperature that has been read.
 */
void fanActivation(float temperature) {
  if (manualOverride) {
    return;
  }
  if (exceededTreshold(temperature)) {
    digitalWrite(FAN_PIN, HIGH);
    Serial.println("Fan ON (Auto)");
  } 
  else {
    digitalWrite(FAN_PIN, LOW);
    Serial.println("Fan OFF (Auto)");
  }
}

/**
 * @brief Manually turns on the fan and overrides automatic control.
 *
 * This function sets the fan to the ON state regardless of the current temperature.
 * It enables manual override, preventing automatic temperature-based control
 * from modifying the fan state until manual override is disabled.
 */
void turnOnFan() {
  manualOverride = true;
  digitalWrite(FAN_PIN, HIGH);
  Serial.println("Fan ON (Manual)");
}

/**
 * @brief Manually turns off the fan and overrides automatic control.
 *
 * This function sets the fan to the OFF state regardless of the current temperature.
 * It enables manual override, preventing automatic temperature-based control
 * from modifying the fan state until manual override is disabled.
 */
void turnOffFan() {
  if (digitalRead(BUTTON) == HIGH) {
    if (digitalRead(FAN_PIN) == HIGH) {
      manualOverride = false;
    }
    else {
      manualOverride = true;
    }
    Serial.println("Boton Presionado");
    digitalWrite(FAN_PIN, LOW);
    Serial.println("Fan OFF (Manual)");
  }
}

/**
 * @brief Prints the current temperature and humidity data to the serial monitor.
 * This function outputs the current temperature and humidity readings to the serial monitor,
 * formatted as "Temperature: <value> °C | Humidity: <value> %".
 * The information helps to monitor the environment and assess the performance of the system.
 *
 * @param temperature is the temperature that has been read.
 * @param humidity is the humidity that has been read.
 */
void printData(float temperature, float humidity) {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C  |  Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
 
/**
 * @brief Reads temperature and humidity from the DHT11 sensor and controls the fan.
 *
 * If the temperature exceeds 30°C, the fan is turned on; otherwise, it remains off.
 * Sensor data and fan status are printed to the serial monitor.
 * If the sensor fails to provide valid readings, an error message is shown instead.
 */
void updateTemperatureFan() {
 
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
 
  // Validate readings
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }
  printData(temperature, humidity);
  fanActivation(temperature);
} 