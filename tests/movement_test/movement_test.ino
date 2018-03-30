// Motor Controller Tutorial
// http://tronixstuff.com/2014/11/25/tutorial-l298n-dual-motor-controller-modules-and-arduino/

// Right motor ports
const int RIGHT_MOTOR_LEVEL = 5;
const int RIGHT_MOTOR_FORWARD = 6;
const int RIGHT_MOTOR_BACKWARD = 7;

// Left motor ports
const int LEFT_MOTOR_LEVEL = 8;
const int LEFT_MOTOR_FORWARD = 9;
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
  pinMode(LEFT_MOTOR_LEVEL, OUTPUT);
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);

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

  beeps(1, 1000);
}

// Turn right for the specified amount of time,
// single side rotation only
// @param time: time in ms to turn for
void right(int time)
{
  // Disable right motor
  analogWrite(RIGHT_MOTOR_LEVEL, 0);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  // Enable left motor forward
  analogWrite(LEFT_MOTOR_LEVEL, 200);
  digitalWrite(LEFT_MOTOR_LEVEL, HIGH);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  // Delay for time
  delay(time);
}

void brake()
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

// Main robot movement loop, runs repeatedly
void loop()
{
  pressToStart();

  right(1000);
  brake();
}
