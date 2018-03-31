/*******************************************************************************
 * InfraredSensor.h
 * Library for reading from infrared sensor.
 * Created by Brian Tom on March 30, 2018.
 * Released into the public domain.
 ******************************************************************************/

#include "Arduino.h"
#include "InfraredSensor.h"

InfraredSensor::InfraredSensor()
{
  m_pin = -1;
}

void InfraredSensor::attach(const int &pin)
{
  // Sensor pin
  m_pin = pin;

  // Sensor pin mode
  pinMode(m_pin, INPUT);
}

void InfraredSensor::detach()
{
  m_pin = -1; // negative pin means no attached sensor
}

bool InfraredSensor::isAttached()
{
  return m_pin >= 0;
}

int InfraredSensor::readState() const
{
  if (isAttached())
  {
    return digitalRead(m_pin);
  }
  else
  {
    return -1;
  }
}
