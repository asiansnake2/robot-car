/*******************************************************************************
 * MotorControllerDemo.ino
 * Demo for the motor controller using a dance.
 * Created by Brian Tom on March 30, 2018.
 * Released into the public domain.
 *
 * Demo assumes the following ports:
 * | Name                    | Port |
 * |-------------------------|------|
 * | Right Motor Power Level | D5   |
 * | Right Motor Forward     | D6   |
 * | Right Motor Backward    | D7   |
 * | Left Motor Forward      | D8   |
 * | Left Motor Backward     | D9   |
 * | Left Motor Power Level  | D10  |
 *
 * Motor Controller Tutorial
 * http://tronixstuff.com/2014/11/25/tutorial-l298n-dual-motor-controller-modules-and-arduino/
 ******************************************************************************/

#include <MotorController.h>

// Right motor ports
const int RIGHT_MOTOR_LEVEL = 5;
const int RIGHT_MOTOR_FORWARD = 6;
const int RIGHT_MOTOR_BACKWARD = 7;

// Left motor ports
const int LEFT_MOTOR_FORWARD = 8;
const int LEFT_MOTOR_BACKWARD = 9;
const int LEFT_MOTOR_LEVEL = 10;

// BEEPER port
const int BEEPER = 12;

// BUTTON port
const int BUTTON = 13;

// Setup pin modes and initialization values
void setup()
{
  // Beep sound pin mode
  // mute = LOW
  // alarm = HIGH
  pinMode(BEEPER, OUTPUT); // digital

  // BUTTON press (BUTTON1) pin mode
  // pressed = LOW
  // unpressed = HIGH
  pinMode(BUTTON, INPUT); // digital
  digitalWrite(BUTTON, HIGH);
}

// Main robot movement loop, runs repeatedly
void loop()
{
  pressToStart();

  // Set up the motor controller
  Motor rightMotor = {RIGHT_MOTOR_LEVEL, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_BACKWARD};
  Motor leftMotor = {LEFT_MOTOR_LEVEL, LEFT_MOTOR_FORWARD, LEFT_MOTOR_BACKWARD};
  MotorController mc(rightMotor, leftMotor, 100);

  // Do the dance
  while (1)
  {
    mc.forward(3000);
    mc.backward(1000);
    mc.setSpeed(75);
    mc.spinLeft(1000);
    mc.spinRight(2000);
    mc.setSpeed(100);
    mc.backward(2000);
    mc.brake(1000);
  }
}

// Beep for the specified amount of time,
// no delay following BEEPER
// @param time: time in ms to BEEPER for
void beep(int time)
{
  digitalWrite(BEEPER, HIGH);
  delay(time);
  digitalWrite(BEEPER, LOW);
}

// Beep specified number of times for a duration,
// with same amount of delay time following each beep
// @param count: number of times to beep
// @param time: time in ms to beep and pause for
void beeps(int count, int time)
{
  for (int i = 0; i < count; i++)
  {
    beep(time);
    delay(time);
  }
}

// Ensures BUTTON is pressed before continuing execution
void pressToStart()
{
  int isPressed;

  isPressed = digitalRead(BUTTON);
  while (isPressed == HIGH)
  {
    isPressed = digitalRead(BUTTON);
  }

  beeps(1, 250);
}
