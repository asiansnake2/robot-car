/*******************************************************************************
 * Testing the ultrasonic sensor with a beep-meter
 * Expects:
 * | Name                   | Port |
 * |------------------------|------|
 * | Ultrasonic Trigger (G) | A0   |
 * | Ultrasonic Echo (RYB)  | A1   |
 * | Beeper                 | D12  |
 * | Button (KEY1)          | D13  |
 *
 * Documentation/Tutorial from sparkfun
 * https://www.sparkfun.com/products/13959
 *
 * GitHub Sample
 * https://github.com/sparkfun/HC-SR04_UltrasonicSensor/blob/master/Firmware/HC-SR04_UltrasonicSensorExample/HC-SR04_UltrasonicSensorExample.ino
 ******************************************************************************/

#include <UltrasonicSensor.h>

// Ultrasonic sensor ports
const int TRIGGER = A0;
const int ECHO = A1;

// Over 400 cm (23200 us pulse) is out of range
const unsigned int MAX_DISTANCE = 23200;

// BEEPER port
const int BEEPER = 12;

// Start BUTTON port
const int BUTTON = 13;

// Setup pin modes and initialization values
void setup()
{
  // View sensor output in Serial monitor
  Serial.begin(9600);

  // Ultrasonic pin modes
  pinMode(TRIGGER, OUTPUT);
  digitalWrite(TRIGGER, LOW);

  // BEEPER sound pin mode
  pinMode(BEEPER, OUTPUT);

  // Start BUTTON pin mode
  pinMode(BUTTON, INPUT);
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

  beeps(1, 1000);
}

void loop()
{
  pressToStart();

  UltrasonicSensor sensor{TRIGGER, ECHO};
  float pulseWidth;

  // Print out distances (delay with beeps)
  while (1)
  {
    pulseWidth = sensor.readPulseWidth();
    // Print out values to Serial if in range
    if (pulseWidth > MAX_DISTANCE)
    {
      Serial.println("Out of Range");
    }
    else
    {
      // beep delay changes proportional to distance
      beeps(1, (float)pulseWidth / 100);
      Serial.print("Distance (cm): ");
      Serial.println(sensor.toCentimeters(pulseWidth));
      Serial.print("Distance (in): ");
      Serial.println(sensor.toInches(pulseWidth));
    }
  }
}
