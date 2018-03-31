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
  InfraredSensor(const int &sensor);

  // Read the state of the sensor
  // Returns LOW when no object in sensing range
  // Returns HIGH when object within sensing range
  int readState() const;

private:
  int SENSOR;
};

#endif
