/**
 * @file TemperatureFanController.h
 * @author Alfonso Rodríguez.
 * @brief Header file for temperature monitoring and fan control using a DHT11 sensor.
 * 
 * This module reads temperature and humidity data from a DHT11 sensor, and controls a fan depending on the measured temperature.
 */

#ifndef TEMPERATURE_FAN_CONTROLLER_H
#define TEMPERATURE_FAN_CONTROLLER_H

#include <DHT.h>

// --- Sensor and fan pin definitions ---
#define DHTPIN A2       ///< Pin where the DHT11 sensor is connected (it will work as a digital pin, in specific the digital pin number 16).
#define DHTTYPE DHT11  ///< Type of the sensor: DHT11
#define FAN_PIN A3     ///< Pin controlling the fan (via transistor) (it will work as a digital pin, in specific the digital pin number 17).

#define TEMPERATURE_TRESHOLD 30.0 /// < Treshold value for the Temperature.

/**
 * @brief Initializes the sensor and fan system.
 * 
 * Sets up serial communication, initializes the DHT11 sensor, and sets the fan pin as output (initially off).
 */
void setupTemperatureFan();

/**
 * @brief Checks whether the temperature exceeds the configured threshold.
 *
 * Compares the given temperature value against the `TEMPERATURE_TRESHOLD` constant.
 * Returns `true` if the value is higher, meaning fan activation may be required.
 *
 * @param temperature The temperature value to evaluate.
 * @return `true` if the threshold is exceeded, `false` otherwise.
 */
bool exceededTreshold(float temperature);

/**
 * @brief Controls the fan depending on the temperature.
 *
 * Turns the fan ON if the temperature is above the threshold, or OFF otherwise.
 * Also outputs a status message ("Fan ON" / "Fan OFF") to the serial monitor.
 *
 * @param temperature The current temperature reading.
 */
void fanActivation(float temperature);

/**
 * @brief Outputs temperature and humidity readings to the serial monitor.
 *
 * Displays the sensor values in a readable format for diagnostics or logging.
 *
 * @param temperature The current temperature value.
 * @param humidity The current humidity value.
 */
void printData(float temperature, float humidity);

/**
 * @brief Reads temperature and humidity, prints values, and controls the fan.
 * 
 * If temperature exceeds 30°C, the fan is turned on. Otherwise, it is turned off.
 * Prints diagnostic messages to the serial monitor.
 */
void updateTemperatureFan();

#endif