#include "DriveSubsystem.h"
#include "../RobotMap.h"
#include <Commands/TeleopDriveCommand.h>

DriveSubsystem::DriveSubsystem()
	: Subsystem("DriveSubsystem"),
	  drive(new RobotDrive(RobotMap::leftDrivePorts[0], RobotMap::leftDrivePorts[1], RobotMap::rightDrivePorts[0], RobotMap::rightDrivePorts[1]))
{
	shifting = new DoubleSolenoid(RobotMap::lowGear, RobotMap::highGear);

	encLeft = new Encoder(RobotMap::leftDriveEncoders[0], RobotMap::leftDriveEncoders[1]);

	encRight = new Encoder(RobotMap::rightDriveEncoders[0], RobotMap::rightDriveEncoders[1]);
}

void DriveSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new TeleopDriveCommand());
}

void DriveSubsystem::Drive(Velocity forward, AngularVelocity turn)
{
	drive->TankDrive((forward / maxHighRobotSpeed + turn / maxHighRobotAngularVelocity)(),
					 (forward / maxHighRobotSpeed - turn / maxHighRobotAngularVelocity)());
}

void DriveSubsystem::ShiftGear(bool high)
{
	currentGear = high;
	shifting->Set(high ? DoubleSolenoid::Value::kForward : DoubleSolenoid::Value::kReverse);
}

bool DriveSubsystem::IsHighGear()
{
	return currentGear;
}

Length DriveSubsystem::getLeftEncoderDistance()
{
	return encLeft->Get() * click;
}

Length DriveSubsystem::getRightEncoderDistance()
{
	return encRight->Get() * click;
}
