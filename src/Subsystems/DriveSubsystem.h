#ifndef DriveSubsystem_H
#define DriveSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <Utils/unitscpp.h>
#include "../Control/ControlSource.h"

class DriveSubsystem : public Subsystem
{
  private:
	std::shared_ptr<RobotDrive> drive;
	std::shared_ptr<DoubleSolenoid> shifting;
	std::shared_ptr<Citrus::EncoderControlSource> encLeft, encRight;
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
