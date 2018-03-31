/*******************************************************************************
 * BlackLineDetectionDemo.ino
 * Demo for pair of infrared sensors under car using beeps for detection type.
 * Created by Brian Tom on March 31, 2018.
 * Released into the public domain.
 *
 * Expects:
 * | Name                        | Port |
 * |-----------------------------|------|
 * | Right Infrared Sensor (RYB) | A2   |
 * | Left Infrared Sensor (RYB)  | A3   |
 * | Beeper                      | D12  |
 * | Button (KEY1)               | D13  |
 ******************************************************************************/

#include <InfraredSensor.h>

// Infrared obstacle avoidance sensors
const int INFRARED_SENSOR_RIGHT = A2;
const int INFRARED_SENSOR_LEFT = A3;

InfraredSensor infraredSensorRight;
InfraredSensor infraredSensorLeft;

// BEEPER port
const int BEEPER = 12;

// Start BUTTON port
const int BUTTON = 13;

// Setup pin modes and initialization values
void setup()
{
  // View sensor output in Serial monitor
  Serial.begin(9600);

  // Attach sensors
  infraredSensorRight.attach(INFRARED_SENSOR_RIGHT);
  infraredSensorLeft.attach(INFRARED_SENSOR_LEFT);

  // BEEPER sound pin mode
  pinMode(BEEPER, OUTPUT);

  // Start BUTTON pin mode
  pinMode(BUTTON, INPUT);
}

void loop()
{
  int infraredSensorStateRight;
  int infraredSensorStateLeft;
  const int beepTime = 1000; // maximum beep time for detection types

  pressToStart();

  // Print out detections and beep based on detection type
  while (1)
  {
    infraredSensorStateRight = infraredSensorRight.readState();
    infraredSensorStateLeft = infraredSensorLeft.readState();

    // No black lines detected
    if (infraredSensorStateRight == LOW && infraredSensorStateLeft == LOW)
    {
      Serial.println("No black lines detected.");
      beeps(1, beepTime);
    }
    // Obstacle on right side
    else if (infraredSensorStateRight == HIGH && infraredSensorStateLeft == LOW)
    {
      Serial.println("Black line detected on right.");
      beeps(1, beepTime / 2);
    }
    // Obstacle on left side
    else if (infraredSensorStateRight == LOW && infraredSensorStateLeft == HIGH)
    {
      Serial.println("Black line detected on left.");
      beeps(1, beepTime / 3);
    }
    // Obstacle on both sides
    else
    {
      Serial.println("Black line detected on both.");
      beeps(1, beepTime / 4);
    }
  }
}

// Beep with BEEPER for the specified amount of time,
// no delay following BEEPER
// @param time: time in ms to beep for
void beep(int time)
{
  digitalWrite(BEEPER, HIGH);
  delay(time);
  digitalWrite(BEEPER, LOW);
}

// Beep with BEEPER for specified number of times for a duration,
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

  beeps(1, 100);
}
