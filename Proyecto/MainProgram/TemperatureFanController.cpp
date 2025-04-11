/**
 * @file TemperatureFanController.cpp
 * @author Alfonso Rodríguez.
 * @brief Implementation file for temperature and fan control using a DHT11 sensor.
 */

 #include "TemperatureFanController.h"

 // Create the DHT sensor object
 DHT dht(DHTPIN, DHTTYPE);
 
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
  * @brief Reads temperature and humidity from the DHT11 sensor and controls the fan.
  *
  * If the temperature exceeds 25°C, the fan is turned on; otherwise, it remains off.
  * Sensor data and fan status are printed to the serial monitor.
  * If the sensor fails to provide valid readings, an error message is shown instead.
  */
 void updateTemperatureFan() {
   delay(2000);  // DHT11 requires delay between reads
 
   float humidity = dht.readHumidity();
   float temperature = dht.readTemperature();
 
   // Validate readings
   if (isnan(humidity) || isnan(temperature)) {
     Serial.println("Failed to read from DHT11 sensor!");
     return;
   }
 
   Serial.print("Temperature: ");
   Serial.print(temperature);
   Serial.print(" °C  |  Humidity: ");
   Serial.print(humidity);
   Serial.println(" %");
 
   // Fan control logic
   if (temperature > 25.0) {
     digitalWrite(FAN_PIN, HIGH);
     Serial.println("Fan ON");
   } 
   else {
     digitalWrite(FAN_PIN, LOW);
     Serial.println("Fan OFF");
   }
 } 