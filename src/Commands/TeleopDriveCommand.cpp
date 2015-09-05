#include "TeleopDriveCommand.h"

TeleopDriveCommand::TeleopDriveCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(driveSubsystem);
}

// Called just before this Command runs the first time
void TeleopDriveCommand::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void TeleopDriveCommand::Execute()
{
	driveSubsystem->Drive(oi->getForwardPower(), oi->getTurningPower());
}

// Make this return true when this Command no longer needs to run execute()
bool TeleopDriveCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void TeleopDriveCommand::End()
{
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TeleopDriveCommand::Interrupted()
{
}
