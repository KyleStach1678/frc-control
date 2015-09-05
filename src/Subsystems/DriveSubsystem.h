#ifndef DriveSubsystem_H
#define DriveSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class DriveSubsystem : public Subsystem {
 private:
  std::unique_ptr<RobotDrive> drive;
  DoubleSolenoid *shifting;
  Encoder *encLeft, *encRight;
  bool currentGear = false;

 public:
  DriveSubsystem();
  void InitDefaultCommand() override;
  void Drive(double forward, double turn);
  void ShiftGear(bool high);
  bool IsHighGear();
  double getLeftEncoderClicks();
  double getRightEncoderClicks();
};

#endif
