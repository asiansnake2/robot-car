/*******************************************************************************
 * InfraredSensor.h
 * Library for reading from infrared sensor.
 * Created by Brian Tom on March 30, 2018.
 * Released into the public domain.
 ******************************************************************************/

#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include "Arduino.h"

// Read data from an infrared sensor
class InfraredSensor
{
public:
  // Constructor takes in sensor port
  InfraredSensor();

  // Attach the sensor for reading
  void attach(const int &pin);

  // Detach the sensor from reading
  void detach();

  // Return true if sensor is attached to pin
  bool isAttached();

  // Read the state of the sensor
  // Returns LOW when no object in sensing range
  // Returns HIGH when object within sensing range
  // Returns -1 when not attached to any sensor
  int readState() const;

private:
  // Stores the pin to read from, negative value if not set
  int m_pin;
};

#endif
