#ifndef DriveSubsystem_H
#define DriveSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <Utils/unitscpp.h>

class DriveSubsystem : public Subsystem
{
  private:
	std::unique_ptr<RobotDrive> drive;
	std::unique_ptr<DoubleSolenoid> shifting;
	std::unique_ptr<Encoder> encLeft, encRight;
	bool currentGear = false;

  public:
	DriveSubsystem();
	void InitDefaultCommand() override;
	void Drive(Velocity forward, AngularVelocity turn);
	void ShiftGear(bool high);
	bool IsHighGear();
	Length getLeftEncoderDistance();
	Length getRightEncoderDistance();
};

#endif
