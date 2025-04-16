/**
 * @file TemperatureFanController.h
 * @author Alfonso Rodríguez.
 * @brief Header file for temperature monitoring and fan control using a DHT11 sensor.
 * 
 * This module reads temperature and humidity data from a DHT11 sensor, and controls a fan depending on the measured temperature.
 */

#ifndef TEMPERATURE_FAN_CONTROLLER_H
#define TEMPERATURE_FAN_CONTROLLER_H

#include <Arduino.h>
#include <DHT.h>

// --- Sensor and fan pin definitions ---
#define DHTPIN A2       ///< Pin where the DHT11 sensor is connected (it will work as a digital pin, in specific the digital pin number 16).
#define DHTTYPE DHT11  ///< Type of the sensor: DHT11
#define FAN_PIN A3     ///< Pin controlling the fan (via transistor) (it will work as a digital pin, in specific the digital pin number 17).

#define TEMPERATURE_TRESHOLD 20.0 /// < Treshold value for the Temperature.

/**
 * @brief Initializes the sensor and fan system.
 * 
 * Sets up serial communication, initializes the DHT11 sensor, and sets the fan pin as output (initially off).
 */
void setupTemperatureFan();

/**
 * @brief Reads temperature and humidity, prints values, and controls the fan.
 * 
 * If temperature exceeds 25°C, the fan is turned on. Otherwise, it is turned off.
 * Prints diagnostic messages to the serial monitor.
 */
void updateTemperatureFan();

#endif