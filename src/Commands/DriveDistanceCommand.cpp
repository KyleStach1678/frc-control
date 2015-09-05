#include <Commands/DriveDistanceCommand.h>

DriveDistanceCommand::DriveDistanceCommand(double meters, double speed) {
  // Use Requires() here to declare subsystem dependencies
  Requires(driveSubsystem);
  this->distanceClicks = meters * 100 * 2.54 / 4 / 3.14 * 360;
  this->speed = speed;
  if (meters < 0) {
    speed = -abs(speed);
  }
  offsetStart = 0;
}

// Called just before this Command runs the first time
void DriveDistanceCommand::Initialize() {
  offsetStart = (driveSubsystem->getLeftEncoderClicks() +
                 driveSubsystem->getRightEncoderClicks()) /
                2.0;
}

// Called repeatedly when this Command is scheduled to run
void DriveDistanceCommand::Execute() { driveSubsystem->Drive(speed, 0); }

// Make this return true when this Command no longer needs to run execute()
bool DriveDistanceCommand::IsFinished() {
  double clicksTravelled = (driveSubsystem->getLeftEncoderClicks() +
                            driveSubsystem->getRightEncoderClicks()) /
                               2.0 -
                           offsetStart;
  return (distanceClicks > 0
              ? driveSubsystem->getLeftEncoderClicks() - offsetStart >
                    distanceClicks
              : driveSubsystem->getLeftEncoderClicks() - offsetStart <
                    distanceClicks);
}

// Called once after isFinished returns true
void DriveDistanceCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistanceCommand::Interrupted() {}
