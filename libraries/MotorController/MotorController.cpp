/*******************************************************************************
 * MotorController.cpp
 * Library for moving the robot.
 * Created by Brian Tom on March 30, 2018.
 * Released into the public domain.
 *
 * Default constructor assumes the following ports:
 * | Name                    | Port |
 * |-------------------------|------|
 * | Right Motor Power Level | D5   |
 * | Right Motor Forward     | D6   |
 * | Right Motor Backward    | D7   |
 * | Left Motor Forward      | D8   |
 * | Left Motor Backward     | D9   |
 * | Left Motor Power Level  | D10  |
 *
 * Default constructor also sets the initial power level to 75%.
 ******************************************************************************/

#include "Arduino.h"
#include "MotorController.h"

MotorController::MotorController()
{
  // Right motor ports
  RIGHT_MOTOR_POWER = 5;
  RIGHT_MOTOR_FORWARD = 6;
  RIGHT_MOTOR_BACKWARD = 7;
  // Left motor ports
  LEFT_MOTOR_FORWARD = 8;
  LEFT_MOTOR_BACKWARD = 9;
  LEFT_MOTOR_POWER = 10;
  // Set default speed to 75%
  m_speed = 75;
  // Right motor pin modes
  pinMode(RIGHT_MOTOR_POWER, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  // Left motor pin modes
  pinMode(LEFT_MOTOR_POWER, OUTPUT);
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
}

MotorController::MotorController(const Motor &rightMotor, const Motor &leftMotor, const float &speed)
{
  // Right motor ports
  RIGHT_MOTOR_POWER = rightMotor.level;
  RIGHT_MOTOR_FORWARD = rightMotor.forward;
  RIGHT_MOTOR_BACKWARD = rightMotor.backward;
  // Left motor ports
  LEFT_MOTOR_FORWARD = leftMotor.forward;
  LEFT_MOTOR_BACKWARD = leftMotor.backward;
  LEFT_MOTOR_POWER = leftMotor.level;
  // Set speed
  setSpeed(speed);
  // Right motor pin modes
  pinMode(RIGHT_MOTOR_POWER, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  // Left motor pin modes
  pinMode(LEFT_MOTOR_POWER, OUTPUT);
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
}

void MotorController::setSpeed(const float &speed)
{
  m_speed = map(constrain(speed, 0, 100), 0, 100, 0, 255);
}

// Get the speed
float MotorController::getSpeed() const
{
  return m_speed;
}

void MotorController::forward(const int &time) const
{
  // Enable right motor forward
  analogWrite(RIGHT_MOTOR_POWER, int(m_speed));
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Enable left motor forward
  analogWrite(LEFT_MOTOR_POWER, int(m_speed));
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

void MotorController::backward(const int &time) const
{
  // Enable right motor backward
  analogWrite(RIGHT_MOTOR_POWER, int(m_speed));
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
  // Enable left motor backward
  analogWrite(LEFT_MOTOR_POWER, int(m_speed));
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  // Delay for time
  delay(time);
}

void MotorController::right(const int &time) const
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR_POWER, 0);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Enable left motor forward
  analogWrite(LEFT_MOTOR_POWER, int(m_speed));
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

void MotorController::spinRight(const int &time) const
{
  // Enable right motor backward
  analogWrite(LEFT_MOTOR_POWER, int(m_speed));
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  // Enable left motor forward
  analogWrite(RIGHT_MOTOR_POWER, int(m_speed));
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

void MotorController::left(const int &time) const
{
  // Disable left motor
  analogWrite(LEFT_MOTOR_POWER, 0);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Enable right motor forward
  analogWrite(RIGHT_MOTOR_POWER, int(m_speed));
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

void MotorController::spinLeft(const int &time) const
{
  // Enable right motor forward
  analogWrite(LEFT_MOTOR_POWER, int(m_speed));
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Enable left motor backward
  analogWrite(RIGHT_MOTOR_POWER, int(m_speed));
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
  // Delay for time
  delay(time);
}

void MotorController::brake() const
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR_POWER, 0);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Disable left motor
  analogWrite(LEFT_MOTOR_POWER, 0);
  digitalWrite(LEFT_MOTOR_POWER, LOW);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
}

void MotorController::brake(const int &time) const
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR_POWER, 0);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Disable left motor
  analogWrite(LEFT_MOTOR_POWER, 0);
  digitalWrite(LEFT_MOTOR_POWER, LOW);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  // Delay for time
  delay(time);
}
