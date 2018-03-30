// Motor Controller Tutorial
// http://tronixstuff.com/2014/11/25/tutorial-l298n-dual-motor-controller-modules-and-arduino/

// Right motor ports
const int RightMotorLevel = 5;
const int RightMotorForward = 6;
const int RightMotorBackward = 7;

// Left motor ports
const int LeftMotorForward = 8;
const int LeftMotorBackward = 9;
const int LeftMotorLevel = 10;

// Beep port
const int Beep = 12;

// Key port
const int Key = 13;

// Setup pin modes and initialization values
void setup()
{
  // Right motor pin modes
  pinMode(RightMotorLevel, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  // Left motor pin modes
  pinMode(LeftMotorLevel, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);

  // Beep sound pin mode
  // mute = LOW
  // alarm = HIGH
  pinMode(Beep, OUTPUT); // digital
  digitalWrite(Beep, LOW);

  // Key press (KEY1) pin mode
  // pressed = LOW
  // unpressed = HIGH
  pinMode(Key, INPUT); // digital
  digitalWrite(Key, HIGH);
}

// Beep for the specified amount of time,
// no delay following beep
// @param time: time in ms to beep for
void beep(int time)
{
  digitalWrite(Beep, HIGH);
  delay(time);
  digitalWrite(Beep, LOW);
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

// Ensures key is pressed before continuing execution
void pressToStart()
{
  int isPressed = digitalRead(Key);
  while (isPressed == HIGH)
  {
    isPressed = digitalRead(Key);
  }

  beeps(1, 1000);
}

// Turn right for the specified amount of time,
// single side rotation only
// @param time: time in ms to turn for
void right(int time)
{
  // Disable right motor
  analogWrite(RightMotorLevel, 0);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  // Enable left motor forward
  analogWrite(LeftMotorLevel, 200);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  // Delay for time
  delay(time);
}

void brake()
{
  // Disable right motor
  analogWrite(RightMotorLevel, 0);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  // Disable left motor
  analogWrite(LeftMotorLevel, 0);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

// Main robot movement loop, runs repeatedly
void loop()
{
  pressToStart();

  right(1000);
  brake();
}
