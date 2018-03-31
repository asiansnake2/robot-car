#include <MotorController.h>
#include <ServoTimer2.h> // uses values in [1000, 2000] for write
#include <UltrasonicSensor.h>

// Right motor ports
const int RIGHT_MOTOR_POWER = 5;
const int RIGHT_MOTOR_FORWARD = 6;
const int RIGHT_MOTOR_BACKWARD = 7;

// Left motor ports
const int LEFT_MOTOR_FORWARD = 8;
const int LEFT_MOTOR_BACKWARD = 9;
const int LEFT_MOTOR_POWER = 10;

const int SERVO = 11;

const int TRIGGER = A0;
const int ECHO = A1;

const int BEEPER = 12;
const int BUTTON = 13;

// Set up the motor controller
Motor rightMotor = {RIGHT_MOTOR_POWER, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_BACKWARD};
Motor leftMotor = {LEFT_MOTOR_POWER, LEFT_MOTOR_FORWARD, LEFT_MOTOR_BACKWARD};
MotorController mc(rightMotor, leftMotor, 70);

int degreesToServoPosition(const int &degrees)
{
  return map(constrain(degrees, 0, 180), 0, 180, 1000, 2000);
}

int servoPositionToDegrees(const int &position)
{
  return map(constrain(position, 1000, 2000), 1000, 2000, 0, 180);
}

ServoTimer2 servo;
const int SERVO_MS_PER_DEGREE = 2; // 2 ms/degree
const int POSITION_RIGHT = degreesToServoPosition(3);
const int POSITION_RIGHT_DIAG = degreesToServoPosition(45);
const int POSITION_FRONT = degreesToServoPosition(90);
const int POSITION_LEFT_DIAG = degreesToServoPosition(135);
const int POSITION_LEFT = degreesToServoPosition(177);

UltrasonicSensor ultrasonic(TRIGGER, ECHO);
const int MIN_STOP_INCHES = 10; // stop within 10 inches of hitting object

void setup()
{
  Serial.begin(9600);

  servo.attach(SERVO);

  pinMode(BEEPER, OUTPUT);

  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);
}

void loop()
{
  pressToStart();

  float left, leftDiag, front, rightDiag, right;

  servo.write(POSITION_FRONT);

  while (1)
  {
    front = readToInchesAtPosition(servo, ultrasonic, POSITION_FRONT);
    if (front < MIN_STOP_INCHES)
    {
      mc.brake();
      left = readToInchesAtPosition(servo, ultrasonic, POSITION_LEFT);
      leftDiag = readToInchesAtPosition(servo, ultrasonic, POSITION_LEFT_DIAG);
      rightDiag = readToInchesAtPosition(servo, ultrasonic, POSITION_RIGHT);
      right = readToInchesAtPosition(servo, ultrasonic, POSITION_RIGHT_DIAG);
      Serial.print(right);
      Serial.print(' ');
      Serial.print(rightDiag);
      Serial.print(' ');
      Serial.print(leftDiag);
      Serial.print(' ');
      Serial.println(left);
      Serial.println();
    }
    else
    {
      mc.forward(500);
    }
  }
}

float readToInchesAtPosition(ServoTimer2 servo, UltrasonicSensor ultrasonic, const int &position)
{
  int originalPosition;   // store the original position to revert to at end
  int diff;               // store the difference between current and future position
  float recordedDistance; // recorded distance from ultrasonic sensor

  // Record the starting position for later
  originalPosition = servo.read();

  // Record distance at the position
  diff = servo.read() - position; // record the difference in positions
  if (diff != 0)                  // only move when necessary
  {
    servo.write(position);                                              // move the servo the the new position
    Serial.println((diff));
    delay(2 * SERVO_MS_PER_DEGREE * abs(servoPositionToDegrees(diff))); // wait for the servo to move
  }
  recordedDistance = ultrasonic.readToInches(); // read the distance

  // Move the servo back to the original position
  servo.write(originalPosition);

  return recordedDistance;
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

  beeps(1, 100);
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
