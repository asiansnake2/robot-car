/*******************************************************************************
 * UltrasonicSensor.cpp
 * Library for reading from ultrasonic sensor HC-SR04.
 * Created by Brian Tom on March 30, 2018.
 * Released into the public domain.
 ******************************************************************************/

#include "Arduino.h"
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(const int &trigger, const int &echo)
{
  // Ultrasonic sensor ports
  TRIGGER = trigger;
  ECHO = echo;
  // Sensor pin modes
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}

float UltrasonicSensor::readPulseWidth()
{
  unsigned long t1;
  unsigned long t2;
  unsigned long pulseWidth;
  float cm;
  float inches;
  // Hold TRIGGER pin high for at least 10us to obtain reading
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  // Time the pulse
  while (digitalRead(ECHO) == 0) // wait for ECHO pulse to begin
    ;
  t1 = micros();                 // start time
  while (digitalRead(ECHO) == 1) // wait for ECHO pulse to end
    ;
  t2 = micros();        // end time
  pulseWidth = t2 - t1; // total time for pulse
  // Return the pulse width
  return pulseWidth;
}

float UltrasonicSensor::readToInches()
{
  return toInches(readPulseWidth());
}

float UltrasonicSensor::readToCentimeters()
{
  return toCentimeters(readPulseWidth());
}

float UltrasonicSensor::toInches(const float &pulseWidth)
{
  return pulseWidth / 148.0;
}

float UltrasonicSensor::toCentimeters(const float &pulseWidth)
{
  return pulseWidth / 58.0;
}
