#include "Arduino.h"
#include "MotorController.h"

MotorController::MotorController()
{
  // Right motor ports
  RIGHT_MOTOR_LEVEL = 5;
  RIGHT_MOTOR_FORWARD = 6;
  RIGHT_MOTOR_BACKWARD = 7;
  // Left motor ports
  LEFT_MOTOR_FORWARD = 8;
  LEFT_MOTOR_BACKWARD = 9;
  LEFT_MOTOR_LEVEL = 10;
  // Set default speed to 75%
  m_speed = 75;
  // Right motor pin modes
  pinMode(RIGHT_MOTOR_LEVEL, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  // Left motor pin modes
  pinMode(LEFT_MOTOR_LEVEL, OUTPUT);
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
}

MotorController::MotorController(const Motor &rightMotor, const Motor &leftMotor, const float &speed)
{
  // Right motor ports
  RIGHT_MOTOR_LEVEL = rightMotor.level;
  RIGHT_MOTOR_FORWARD = rightMotor.forward;
  RIGHT_MOTOR_BACKWARD = rightMotor.backward;
  // Left motor ports
  LEFT_MOTOR_FORWARD = leftMotor.forward;
  LEFT_MOTOR_BACKWARD = leftMotor.backward;
  LEFT_MOTOR_LEVEL = leftMotor.level;
  // Set speed
  setSpeed(speed);
  // Right motor pin modes
  pinMode(RIGHT_MOTOR_LEVEL, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  // Left motor pin modes
  pinMode(LEFT_MOTOR_LEVEL, OUTPUT);
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
  analogWrite(RIGHT_MOTOR_LEVEL, int(m_speed));
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Enable left motor forward
  analogWrite(LEFT_MOTOR_LEVEL, int(m_speed));
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

void MotorController::backward(const int &time) const
{
  // Enable right motor backward
  analogWrite(RIGHT_MOTOR_LEVEL, int(m_speed));
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
  // Enable left motor backward
  analogWrite(LEFT_MOTOR_LEVEL, int(m_speed));
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  // Delay for time
  delay(time);
}

void MotorController::right(const int &time) const
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR_LEVEL, 0);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Enable left motor forward
  analogWrite(LEFT_MOTOR_LEVEL, int(m_speed));
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

void MotorController::spinRight(const int &time) const
{
  // Enable right motor backward
  analogWrite(LEFT_MOTOR_LEVEL, int(m_speed));
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  // Enable left motor forward
  analogWrite(RIGHT_MOTOR_LEVEL, int(m_speed));
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

void MotorController::left(const int &time) const
{
  // Disable left motor
  analogWrite(LEFT_MOTOR_LEVEL, 0);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Enable right motor forward
  analogWrite(RIGHT_MOTOR_LEVEL, int(m_speed));
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

void MotorController::spinLeft(const int &time) const
{
  // Enable right motor forward
  analogWrite(LEFT_MOTOR_LEVEL, int(m_speed));
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Enable left motor backward
  analogWrite(RIGHT_MOTOR_LEVEL, int(m_speed));
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
  // Delay for time
  delay(time);
}

void MotorController::brake() const
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR_LEVEL, 0);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Disable left motor
  analogWrite(LEFT_MOTOR_LEVEL, 0);
  digitalWrite(LEFT_MOTOR_LEVEL, LOW);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
}

void MotorController::brake(const int &time) const
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR_LEVEL, 0);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Disable left motor
  analogWrite(LEFT_MOTOR_LEVEL, 0);
  digitalWrite(LEFT_MOTOR_LEVEL, LOW);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  // Delay for time
  delay(time);
}
