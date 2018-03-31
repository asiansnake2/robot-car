# robot-car

## Things to accomplish
* [COMPLETED] Understand how to move the car
* [COMPLETED] Move the car (with remote control)
* Build obstacle course to test capabilites
  * Ramp
  * Maze navigation
  * Rocky surfaces
* Autonomous movement through obstacle course
* [COMPLETED] Geiger Counter Obstacle Detection

## Instructions
To use the libraries and test code on your own [Kuman Arduino UNO Bluetooth / Infrared Remote Control Smart Robot Car Kit SM11](http://www.kumantech.com/kuman-arduino-uno-bluetooth-irafred-remote-control-smart-robot-car-kit-sm11_p0415.html):
1. Download the Git repo
2. Copy the `libraries` directory to your local Arduinio `libraries` folder (typically at `C:\Program Files (x86)\Arduino\libraries` for Windows)
3. In the Arduino IDE, open a demo sketch under `File > Examples > [Library Name]`
4. Ensure your robots ports match the ports inside the sketch (or change either one so they match)
5. Upload and run

## Issues
* Left signal LEDs do not light up, diode is always reverse biased and never changes direction
* Connecting either IR sensor (top sensors) causes issues with uploading to robot, disconnect prior to uploading
* [FIXED] Motor controller does not send out signals to activate motors when correct inputs are given
