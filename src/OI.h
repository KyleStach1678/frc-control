#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "RobotMap.h"

class OI {
 private:
  std::unique_ptr<Joystick> driverRight =
      std::unique_ptr<Joystick>(new Joystick(RobotMap::rightDriverStick));

  std::unique_ptr<Joystick> driverLeft =
      std::unique_ptr<Joystick>(new Joystick(RobotMap::leftDriverStick));

  std::unique_ptr<Joystick> manipulator =
      std::unique_ptr<Joystick>(new Joystick(2));

  std::unique_ptr<JoystickButton> shiftLow;

  std::unique_ptr<JoystickButton> shiftHigh =
      std::unique_ptr<JoystickButton>(new JoystickButton(driverRight.get(), 3));

  std::unique_ptr<JoystickButton> driveDistance =
      std::unique_ptr<JoystickButton>(new JoystickButton(driverRight.get(), 1));

 public:
  OI();
  double getForwardPower();
  double getTurningPower();
  double getElevatorPower();
};

#endif
