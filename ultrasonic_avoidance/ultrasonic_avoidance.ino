/*******************************************************************************
 * ultrasonic_avoidance.ino
 * Based off KUMAN program for robot car
 * Created by Brian Tom on March 30, 2018.
 * Released into the public domain.
 *
 * Ports:
 * | Name                    | Port |
 * |-------------------------|------|
 * | Right Motor Power Level | D5   |
 * | Right Motor Forward     | D6   |
 * | Right Motor Backward    | D7   |
 * | Left Motor Forward      | D8   |
 * | Left Motor Backward     | D9   |
 * | Left Motor Power Level  | D10  |
 * | Servo                   | D11  |
 * | Beeper                  | D12  |
 * | Button                  | D13  |
 * | Ultrasonic Trigger      | A0   |
 * | Ultrasonic Echo         | A1   |
 *
 ******************************************************************************/

#include <Servo.h>            // Library for controlling head turning servo
#include <UltrasonicSensor.h> // Ultrasonic sensor library
#include <MotorController.h>  // Motor controller library

// Motor Controller
const int RIGHT_MOTOR_POWER = 5;
const int RIGHT_MOTOR_FORWARD = 6;
const int RIGHT_MOTOR_BACKWARD = 7;
const int LEFT_MOTOR_FORWARD = 8;
const int LEFT_MOTOR_BACKWARD = 9;
const int LEFT_MOTOR_POWER = 10;
const int DEFAULT_MOVE_TIME = 100; // milliseconds
const int DEFAULT_SPEED = 75;
Motor rightMotor = {RIGHT_MOTOR_POWER, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_BACKWARD};
Motor leftMotor = {LEFT_MOTOR_POWER, LEFT_MOTOR_FORWARD, LEFT_MOTOR_BACKWARD};
MotorController mc(rightMotor, leftMotor, DEFAULT_SPEED);

// Servo for controlling head rotation
Servo servo;
const int SERVO = 11;
const int SERVO_FRONT = 90; // servo face forward
const int SERVO_RIGHT = 3;  // servo face full right = 0
const int SERVO_LEFT = 177; // servo face full left = 180

// Utility pins
const int BEEPER = 12;
const int BUTTON = 13;

// Ultrasonic sensor
const int TRIGGER = A0;
const int ECHO = A1;
UltrasonicSensor ultrasonic(TRIGGER, ECHO);

// Movement directions
enum Direction
{
  Forward,
  Backward,
  Left,
  Right,
  Brake,
};

// Definitions
const int stabilizeTime = 200; // delay time for servo to move to position
int distanceFront = 0;         // front distance
int distanceRight = 0;         // right distance
int distanceLeft = 0;          // left distance
int direction = Forward;       // direction to move in

void setup()
{
  Serial.begin(9600); // Initialize serial monitor

  // Right motor pin modes
  pinMode(RIGHT_MOTOR_POWER, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  // Left motor pin modes
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(LEFT_MOTOR_POWER, OUTPUT);

  // Attach servo motor
  servo.attach(SERVO);

  // Button, beeper pin modes
  pinMode(BUTTON, INPUT);
  pinMode(BEEPER, OUTPUT);

  // Ultrasonic pin modes
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);

  // Button set to unpressed state (=HIGH)
  digitalWrite(BUTTON, HIGH);
}

// Main loop
void loop()
{
  pressToStart(); // Press the button to start

  while (true)
  {
    servo.write(90); // Make the servo motor ready position Prepare the next measurement
    detect();        // Measuring angle and determine which direction to go to

    switch (direction)
    {
    case Forward:
      mc.forward(DEFAULT_MOVE_TIME);
      Serial.println("Forward");
    case Backward:
      mc.backward(DEFAULT_MOVE_TIME);
      Serial.println("Backward");
    case Left:
      mc.spinLeft(DEFAULT_MOVE_TIME);
      Serial.println("Left");
    case Right:
      mc.spinRight(DEFAULT_MOVE_TIME);
      Serial.println("Right");
    case Brake:
      mc.brake(DEFAULT_MOVE_TIME);
      Serial.println("Brake");
    case default:
      Serial.println("Invalid direction.");
    }
  }
}

// Measuring three angles (0, 90, 180)
void detect()
{
  // Read front distance
  distanceFront = measureFront();

  // If the front distance less than 10 cm
  if (distanceFront < 10)
  {
    mc.backward(500);
  }

  // If the front distance less than 20 cm
  if (distanceFront < 20)
  {
    mc.brake(100);                // Remove the output data
    distanceLeft = measureLeft(); // Read the left distance
    // delay(stabilizeTime); // Wait for the servo motor to stabilize
    distanceRight = measureRight(); // Read the right distance
    // delay(stabilizeTime); // Wait for the servo motor to stabilize

    // If the left distance and right distance
    // less than 10 cm move backwards
    if (distanceLeft < 10 && distanceRight < 10)
    {
      direction = Backward; // Walk backwards
    }
    // If the distance is greater than the right distance on the left
    else if (distanceLeft > distanceRight)
    {
      direction = Left; // Left
    }
    // If the distance is less than or equal to the distance on the right
    else if (distanceLeft < distanceRight)
    {
      direction = Right; // right
    }
  }
  // If the front is greater than 25 cm
  else
  {
    direction = Forward; // Walk forward
  }
}

// Measure the distance ahead
float measureFront()
{
  servo.write(SERVO_FRONT);
  delay(stabilizeTime);
  float distance = ultrasonic.readToCentimeters();
  Serial.print("Distance Front: ");
  Serial.println(distance);
  return distance;
}

// Measure the distance on the left
float measureLeft()
{
  servo.write(SERVO_LEFT);
  delay(stabilizeTime);
  float distance = ultrasonic.readToCentimeters();
  Serial.print("Distance Left: ");
  Serial.println(distance);
  return distance;
}

// Measure the distance on the right
float measureRight()
{
  servo.write(SERVO_RIGHT);
  delay(stabilizeTime);
  float distance = ultrasonic.readToCentimeters();
  Serial.print("Distance Right: ");
  Serial.println(distance);
  return distance;
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
