#include <Commands/DriveDistanceCommand.h>

DriveDistanceCommand::DriveDistanceCommand(Length meters, Velocity speed) {
  // Use Requires() here to declare subsystem dependencies
  Requires(driveSubsystem);
  this->distanceClicks = meters;
  this->speed = speed;
  offsetStart = 0;
}

// Called just before this Command runs the first time
void DriveDistanceCommand::Initialize() {
  offsetStart = (driveSubsystem->getLeftEncoderDistance() +
                 driveSubsystem->getRightEncoderDistance()) /
                2.0;
}

// Called repeatedly when this Command is scheduled to run
void DriveDistanceCommand::Execute() {
  driveSubsystem->Drive((speed / maxHighRobotSpeed)(), 0);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistanceCommand::IsFinished() {
  Length clicksTravelled = (driveSubsystem->getLeftEncoderDistance() +
                            driveSubsystem->getRightEncoderDistance()) /
                               2.0 -
                           offsetStart;
  return (distanceClicks > 0)
             ? (clicksTravelled > distanceClicks)
             : (clicksTravelled - offsetStart < distanceClicks);
}

// Called once after isFinished returns true
void DriveDistanceCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistanceCommand::Interrupted() {}
