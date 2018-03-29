// Documentation/Tutorial from sparkfun
// https://www.sparkfun.com/products/13959

// GitHub Sample
// https://github.com/sparkfun/HC-SR04_UltrasonicSensor/blob/master/Firmware/HC-SR04_UltrasonicSensorExample/HC-SR04_UltrasonicSensorExample.ino

// Utrasonic sensor ports
int Trigger = A0;
int Echo = A1;

// Over 400 cm (23200 us pulse) is out of range
const unsigned int MAX_DISTANCE = 23200;

// Beep port
int Beep = 12;

// Key port
int Key = 13;

// Setup pin modes and initialization values
void setup()
{
  // View sensor output in Serial monitor
  Serial.begin(9600);

  // Ultrasonic pin modes
  pinMode(Trigger, OUTPUT);
  digitalWrite(Trigger, LOW);
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

// Mesaure distance using ultrasonic sensor
// Print out both inches and cm measurements
void readDistance()
{
  unsigned long t1;
  unsigned long t2;
  unsigned long pulseWidth;
  float cm;
  float inches;

  // Hold trigger pin high for at least 10us to obtain reading
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);

  // Time the pulse
  while (digitalRead(Echo) == 0) // wait for echo pulse to begin
    ;
  t1 = micros();                 // start time
  while (digitalRead(Echo) == 1) // wait for echo pulse to end
    ;
  t2 = micros();        // end time
  pulseWidth = t2 - t1; // total time for pulse

  // Convert pulse to cm and inches
  cm = pulseWidth / 58.0;
  inches = pulseWidth / 148.0;

  // Print out values to Serial if in range
  if (pulseWidth > MAX_DISTANCE)
  {
    Serial.print("Out of Range");
  }
  else
  {
    Serial.print("Distance (cm): ");
    Serial.println(cm);
    Serial.print("Distance (in): ");
    Serial.println(inches);
  }
}

void loop()
{
  pressToStart();

  // Print out distances every half second
  while (1)
  {
    readDistance();
    delay(500);
  }
}
