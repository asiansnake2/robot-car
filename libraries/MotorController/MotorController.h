/*******************************************************************************
 * MotorController.h
 * Library for moving the robot.
 * Created by Brian Tom on March 30, 2018.
 * Released into the public domain.
 ******************************************************************************/

#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Arduino.h"

// Motor contains 3 port values
struct Motor
{
  int power;
  int forward;
  int backward;
};

// Controls the robots movement
class MotorController
{
public:
  // Constructor with motor controller ports and speed
  MotorController(const Motor &rightMotor, const Motor &leftMotor, const float &speed);

  // Set the speed of the movement
  void setSpeed(const float &speed);
  // Get the current movement speed of the robot
  float getSpeed() const;

  // Move forward for the specified amount of time at set speed
  // @param time: minimum time in ms to move for
  void forward(const int &time) const;
  // Move backward for the specified amount of time at set speed
  // @param time: minimum time in ms to move for
  void backward(const int &time) const;
  // Turn right for the specified amount of time at set speed,
  // single side rotation only
  // @param time: minimum time in ms to turn for
  void right(const int &time) const;
  // Spin right for the specified amount of time at the set speed,
  // dual side rotation
  // @param time: minimum time in ms to turn for
  void spinRight(const int &time) const;
  // Turn left for the specified amount of time at set speed,
  // single side rotation only
  // @param time: minimum time in ms to turn for
  void left(const int &time) const;
  // Spin left for the specified amount of time at the set speed,
  // dual side rotation
  // @param time: minimum time in ms to turn for
  void spinLeft(const int &time) const;
  // Stop the robot with no minimum brake time
  void brake() const;
  // Stop the robot
  // @param time: minimum time in ms to brake for
  void brake(const int &time) const;

private:
  // Right and left ports
  Motor RIGHT_MOTOR;
  Motor LEFT_MOTOR;
  // MotorController speed (percentage of maximum speed)
  float m_speed;
};

#endif
