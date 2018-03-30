// Motor Controller Tutorial
// http://tronixstuff.com/2014/11/25/tutorial-l298n-dual-motor-controller-modules-and-arduino/

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
  // Right motor pin modes
  pinMode(RIGHT_MOTOR_LEVEL, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);

  // Left motor pin modes
  pinMode(LEFT_MOTOR_LEVEL, OUTPUT);
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);

  // Beep sound pin mode
  // mute = LOW
  // alarm = HIGH
  pinMode(BEEPER, OUTPUT); // digital
  digitalWrite(BEEPER, LOW);

  // BUTTON press (BUTTON1) pin mode
  // pressed = LOW
  // unpressed = HIGH
  pinMode(BUTTON, INPUT); // digital
  digitalWrite(BUTTON, HIGH);
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

// Move forward for the specified amount of time
// @param time: minimum time in ms to move for
// @param speed: percentage of max speed
void forward(int time, float speed)
{
  int mappedSpeed = map(speed, 0, 100, 0, 255);
  // Enable right motor forward
  analogWrite(RIGHT_MOTOR_LEVEL, int(mappedSpeed));
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Enable left motor forward
  analogWrite(LEFT_MOTOR_LEVEL, int(mappedSpeed));
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

// Move backward for the specified amount of time
// @param time: minimum time in ms to move for
// @param speed: percentage of max speed
void backward(int time, float speed)
{
  // Enable right motor backward
  analogWrite(RIGHT_MOTOR_LEVEL, int(map(speed, 0, 100, 0, 255)));
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
  // Enable left motor backward
  analogWrite(LEFT_MOTOR_LEVEL, int(map(speed, 0, 100, 0, 255)));
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  // Delay for time
  delay(time);
}

// Turn right for the specified amount of time,
// single side rotation only
// @param time: minimum time in ms to turn for
// @param speed: percentage of max speed
void right(int time, float speed)
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR_LEVEL, 0);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Enable left motor forward
  analogWrite(LEFT_MOTOR_LEVEL, int(map(speed, 0, 100, 0, 255)));
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

// Turn left for the specified percentage of max speed,
// single side rotation only
// @param time: minimum time in ms to turn for
// @param speed: percentage of max speed
void left(int time, float speed)
{
  // Disable left motor
  analogWrite(LEFT_MOTOR_LEVEL, 0);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  // Enable right motor forward
  analogWrite(RIGHT_MOTOR_LEVEL, int(map(speed, 0, 100, 0, 255)));
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Delay for time
  delay(time);
}

// Stop the robot
// @param time: minimum time in ms to brake for
void brake(int time)
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

// Main robot movement loop, runs repeatedly
void loop()
{
  pressToStart();

  forward(5000, 50);
  forward(2000, 75);
  forward(1000, 100);
  backward(1000, 100);
  right(1000, 75);
  left(1000, 75);
  brake(0);
}
