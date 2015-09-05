#include "ShiftCommand.h"

ShiftCommand::ShiftCommand(bool highGear) {
  this->highGear = highGear;
  Requires(driveSubsystem);
}

// Called just before this Command runs the first time
void ShiftCommand::Initialize() { driveSubsystem->ShiftGear(highGear); }

// Called repeatedly when this Command is scheduled to run
void ShiftCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ShiftCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void ShiftCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShiftCommand::Interrupted() {}
