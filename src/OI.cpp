#include "OI.h"
#include <Commands/ShiftCommand.h>
#include <Commands/DriveDistanceCommand.h>

OI::OI()
	: driverRight(new Joystick(RobotMap::rightDriverStick)), driverLeft(new Joystick(RobotMap::leftDriverStick)), manipulator(new Joystick(2)),
	  shiftLow(new JoystickButton(driverLeft.get(), 3)), shiftHigh(new JoystickButton(driverRight.get(), 3)),
	  driveDistance(new JoystickButton(driverRight.get(), 1))
{
	shiftLow->WhenPressed(new ShiftCommand(false));
	shiftHigh->WhenPressed(new ShiftCommand(true));
	driveDistance->WhenPressed(new DriveDistanceCommand(1.5));
}

double OI::getForwardPower()
{
	return -driverLeft->GetRawAxis(1);
}

double OI::getTurningPower()
{
	return -driverRight->GetRawAxis(0);
}

double OI::getElevatorPower()
{
	return -manipulator->GetRawAxis(1);
}
