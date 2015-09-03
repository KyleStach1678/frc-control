package org.usfirst.frc.team1678.robot.commands;

import org.usfirst.frc.team1678.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;

public class DriveDistanceCommand extends Command {
	
	double encoderOffset;

	double driveDistance;
	public DriveDistanceCommand(double distance) {
		requires(Robot.drive);
		driveDistance=distance;
	}

	@Override
	protected void initialize() {
		encoderOffset = Robot.drive.getLeftEncoderClicks();
	}

	@Override
	protected void execute() {
		// TODO Auto-generated method stub
		Robot.drive.Drive(.5, 0.0);
	}

	@Override
	protected boolean isFinished() {
		// TODO Auto-generated method stub
		return Math.abs(driveDistance) < Math.abs(Robot.drive.getLeftEncoderClicks() - encoderOffset);
	}

	@Override
	protected void end() {
		Robot.drive.Drive(0, 0);
	}

	@Override
	protected void interrupted() {
		// TODO Auto-generated method stub

	}

}
