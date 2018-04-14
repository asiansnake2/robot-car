/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;        // create servo object to control a servo
const int SERVO = 11; // servo pin

int pos = 0; // variable to store the servo position

void setup()
{
  Serial.begin(9600);
    myservo.attach(SERVO); // attaches the servo on pin 9 to the servo object
}

void loop()
{
    // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    for (pos = 0; pos <= 180; pos += 1)
    {
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        Serial.println(pos);
        delay(15); // waits 15ms for the servo to reach the position
    }
    // goes from 180 degrees to 0 degrees
    for (pos = 180; pos >= 0; pos -= 1)
    {
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        Serial.println(pos);
        delay(15); // waits 15ms for the servo to reach the position
    }
}
