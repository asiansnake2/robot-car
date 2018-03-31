/*******************************************************************************
 * InfraredSensor.h
 * Library for reading from infrared sensor.
 * Created by Brian Tom on March 30, 2018.
 * Released into the public domain.
 ******************************************************************************/

#include "Arduino.h"
#include "InfraredSensor.h"

InfraredSensor::InfraredSensor(const int &sensor)
{
  // Sensor port
  SENSOR = sensor;

  // Sensor pin mode
  pinMode(SENSOR, INPUT);
}

int InfraredSensor::readState() const
{
  return digitalRead(SENSOR);
}
