/*******************************************************************************
 * MotorController.cpp
 * Library for moving the robot.
 * Created by Brian Tom on March 30, 2018.
 * Released into the public domain.
 ******************************************************************************/

#include "Arduino.h"
#include "MotorController.h"

MotorController::MotorController(const Motor &rightMotor, const Motor &leftMotor, const float &speed)
{
  // Right and left motor ports
  RIGHT_MOTOR = rightMotor;
  LEFT_MOTOR = leftMotor;
  // Set speed
  setSpeed(speed);
  // Right motor pin modes
  pinMode(RIGHT_MOTOR.power, OUTPUT);
  pinMode(RIGHT_MOTOR.forward, OUTPUT);
  pinMode(RIGHT_MOTOR.backward, OUTPUT);
  // Left motor pin modes
  pinMode(LEFT_MOTOR.power, OUTPUT);
  pinMode(LEFT_MOTOR.forward, OUTPUT);
  pinMode(LEFT_MOTOR.backward, OUTPUT);
}

void MotorController::setSpeed(const float &speed)
{
  m_speed = map(constrain(speed, 0, 100), 0, 100, 0, 255);
}

float MotorController::getSpeed() const
{
  return m_speed;
}

void MotorController::forward(const int &time) const
{
  // Enable right motor forward
  analogWrite(RIGHT_MOTOR.power, int(m_speed));
  digitalWrite(RIGHT_MOTOR.forward, HIGH);
  digitalWrite(RIGHT_MOTOR.backward, LOW);
  // Enable left motor forward
  analogWrite(LEFT_MOTOR.power, int(m_speed));
  digitalWrite(LEFT_MOTOR.forward, HIGH);
  digitalWrite(LEFT_MOTOR.backward, LOW);
  // Delay for time
  delay(time);
}

void MotorController::backward(const int &time) const
{
  // Enable right motor backward
  analogWrite(RIGHT_MOTOR.power, int(m_speed));
  digitalWrite(RIGHT_MOTOR.forward, LOW);
  digitalWrite(RIGHT_MOTOR.backward, HIGH);
  // Enable left motor backward
  analogWrite(LEFT_MOTOR.power, int(m_speed));
  digitalWrite(LEFT_MOTOR.forward, LOW);
  digitalWrite(LEFT_MOTOR.backward, HIGH);
  // Delay for time
  delay(time);
}

void MotorController::right(const int &time) const
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR.power, 0);
  digitalWrite(RIGHT_MOTOR.forward, LOW);
  digitalWrite(RIGHT_MOTOR.backward, LOW);
  // Enable left motor forward
  analogWrite(LEFT_MOTOR.power, int(m_speed));
  digitalWrite(LEFT_MOTOR.forward, HIGH);
  digitalWrite(LEFT_MOTOR.backward, LOW);
  // Delay for time
  delay(time);
}

void MotorController::spinRight(const int &time) const
{
  // Enable left motor forward
  analogWrite(RIGHT_MOTOR.power, int(m_speed));
  digitalWrite(RIGHT_MOTOR.forward, HIGH);
  digitalWrite(RIGHT_MOTOR.backward, LOW);
  // Enable right motor backward
  analogWrite(LEFT_MOTOR.power, int(m_speed));
  digitalWrite(LEFT_MOTOR.forward, LOW);
  digitalWrite(LEFT_MOTOR.backward, HIGH);
  // Delay for time
  delay(time);
}

void MotorController::left(const int &time) const
{
  // Enable right motor forward
  analogWrite(RIGHT_MOTOR.power, int(m_speed));
  digitalWrite(RIGHT_MOTOR.forward, HIGH);
  digitalWrite(RIGHT_MOTOR.backward, LOW);
  // Disable left motor
  analogWrite(LEFT_MOTOR.power, 0);
  digitalWrite(LEFT_MOTOR.forward, LOW);
  digitalWrite(LEFT_MOTOR.backward, LOW);
  // Delay for time
  delay(time);
}

void MotorController::spinLeft(const int &time) const
{
  // Enable left motor backward
  analogWrite(RIGHT_MOTOR.power, int(m_speed));
  digitalWrite(RIGHT_MOTOR.forward, LOW);
  digitalWrite(RIGHT_MOTOR.backward, HIGH);
  // Enable right motor forward
  analogWrite(LEFT_MOTOR.power, int(m_speed));
  digitalWrite(LEFT_MOTOR.forward, HIGH);
  digitalWrite(LEFT_MOTOR.backward, LOW);
  // Delay for time
  delay(time);
}

void MotorController::brake() const
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR.power, 0);
  digitalWrite(RIGHT_MOTOR.forward, LOW);
  digitalWrite(RIGHT_MOTOR.backward, LOW);
  // Disable left motor
  analogWrite(LEFT_MOTOR.power, 0);
  digitalWrite(LEFT_MOTOR.forward, LOW);
  digitalWrite(LEFT_MOTOR.backward, LOW);
}

void MotorController::brake(const int &time) const
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR.power, 0);
  digitalWrite(RIGHT_MOTOR.forward, LOW);
  digitalWrite(RIGHT_MOTOR.backward, LOW);
  // Disable left motor
  analogWrite(LEFT_MOTOR.power, 0);
  digitalWrite(LEFT_MOTOR.forward, LOW);
  digitalWrite(LEFT_MOTOR.backward, LOW);
  // Delay for time
  delay(time);
}
