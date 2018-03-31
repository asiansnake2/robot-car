/*******************************************************************************
 * UltrasonicSensor.h
 * Library for reading from ultrasonic sensor HC-SR04.
 * Created by Brian Tom on March 30, 2018.
 * Released into the public domain.
 ******************************************************************************/

#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

class UltrasonicSensor
{
public:
  // Default constructor
  UltrasonicSensor();
  // Constructor to specify sensor ports
  UltrasonicSensor(const int &trigger, const int &echo);

  // Read pulse width from echo
  float readPulseWidth();
  // Read pulse width and convert to inches
  float readToInches();
  // Read pulse width and convert to cm
  float readToCentimeters();

  // Convert pulse width to inches
  // @param pulseWidth: width of pulse to convert
  float toInches(const float &pulseWidth);
  // Convert pulse width to centimeters
  // @param pulseWidth: width of pulse to convert
  float toCentimeters(const float &pulseWidth);

private:
  // Ultrasonic sensor ports
  int TRIGGER;
  int ECHO;
};

#endif
