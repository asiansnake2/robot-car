#ifndef MOTORCONTROLLER_H

#define MOTORCONTROLLER_H

struct Motor
{
  int level;
  int forward;
  int backward;
};

class MotorController
{
public:
  // Default constructor, speed initially set to 75%
  MotorController();
  // Constructor with custom ports and speed
  MotorController(const Motor &rightMotor, const Motor &leftMotor, const float &speed);

  // Speed
  void setSpeed(const float &speed);
  float getSpeed() const;

  // Movement
  // Move forward for the specified amount of time at set speed
  // @param time: minimum time in ms to move for
  void forward(const int &time) const;
  // Move backward for the specified amount of time at set speed
  // @param time: minimum time in ms to move for
  void backward(const int &time) const;
  // Turn right for the specified amount of time at set speed,
  // single side rotation only
  // @param time: minimum time in ms to turn for
  void right(const int &time) const;
  // Spin right for the specified amount of time at the set speed,
  // dual side rotation
  // @param time: minimum time in ms to turn for
  void spinRight(const int &time) const;
  // Turn left for the specified amount of time at set speed,
  // single side rotation only
  // @param time: minimum time in ms to turn for
  void left(const int &time) const;
  // Spin left for the specified amount of time at the set speed,
  // dual side rotation
  // @param time: minimum time in ms to turn for
  void spinLeft(const int &time) const;
  // Stop the robot with no minimum brake time
  void brake() const;
  // Stop the robot
  // @param time: minimum time in ms to brake for
  void brake(const int &time) const;

private:
  // Right motor ports
  int RIGHT_MOTOR_LEVEL;
  int RIGHT_MOTOR_FORWARD;
  int RIGHT_MOTOR_BACKWARD;
  // Left motor ports
  int LEFT_MOTOR_FORWARD;
  int LEFT_MOTOR_BACKWARD;
  int LEFT_MOTOR_LEVEL;
  // MotorController speed (percentage of maximum speed)
  float m_speed;
};

#endif
