/*
 * Ultrasonic Avoidance
 * Based off KUMAN program for robot car
 */

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
Motor rightMotor = {RIGHT_MOTOR_POWER, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_BACKWARD};
Motor leftMotor = {LEFT_MOTOR_POWER, LEFT_MOTOR_FORWARD, LEFT_MOTOR_BACKWARD};
MotorController mc(rightMotor, leftMotor, 75);

// Servo for controlling head rotation
Servo servo;
const int SERVO = 11;
const int SERVO_FRONT = 90; // front
const int SERVO_RIGHT = 3;  // full right = 0
const int SERVO_LEFT = 177; // full left = 180

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
  Right
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

  pinMode(LEFT_MOTOR_POWER, OUTPUT);     // Define 5 pin for PWM output
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);  // Define 6 pin for the output (PWM)
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT); // Define 7 pin for the output (PWM)
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);   // Define 8 pin for the output (PWM)
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);  // Define 9 pin for the output (PWM)
  pinMode(RIGHT_MOTOR_POWER, OUTPUT);    // Define 10 pin for PWM output

  pinMode(BUTTON, INPUT);  // Set button as input
  pinMode(BEEPER, OUTPUT); // Set buzzer as output

  pinMode(ECHO, INPUT);     // Define the ultrasound Echo pin
  pinMode(TRIGGER, OUTPUT); // Define the ultrasound Trigger pin

  digitalWrite(BUTTON, HIGH); //Initialize button
  digitalWrite(BEEPER, LOW);  // set buzzer mute

  servo.attach(SERVO); // Define the servo motor output 11 pin (PWM)
}

// Main loop
void loop()
{
  pressToStart(); // Press the button to start

  while (true)
  {
    servo.write(90); // Make the servo motor ready position Prepare the next measurement
    detect();        // Measuring angle and determine which direction to go to

    if (direction == Backward)
    {
      mc.backward(3000);
      mc.spinLeft(0); // Move slightly to the left (to prevent stuck in dead end lane)
      Serial.println("Reverse");
    }

    if (direction == Right)
    {
      mc.backward(0);
      mc.spinRight(2000);
      Serial.println("Right");
    }

    if (direction == Left)
    {
      mc.backward(0);
      mc.spinLeft(2000);
      Serial.println("Left");
    }

    if (direction == Forward)
    {
      mc.forward(3000);
      Serial.println("Forward");
    }
  }
}

// Measuring three angles (0, 90, 180)
void detect()
{
  distanceFront = measureFront(); // Read in front of the distance

  if (distanceFront < 20) // If the front distance less than 6 cm
  {
    mc.brake(100); // Remove the output data
    mc.backward(500);
  }

  if (distanceFront < 30) // If the front distance less than 10 cm
  {
    mc.brake(100);                // Remove the output data
    distanceLeft = measureLeft(); // Read the left distance
    // delay(stabilizeTime); // Wait for the servo motor to stabilize
    distanceRight = measureRight(); // Read the right distance
    // delay(stabilizeTime); // Wait for the servo motor to stabilize

    // If the left distance and right distance
    // less than 20 cm move backwards
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
