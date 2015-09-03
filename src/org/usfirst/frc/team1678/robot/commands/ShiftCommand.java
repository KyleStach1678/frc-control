package org.usfirst.frc.team1678.robot.commands;

import org.usfirst.frc.team1678.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;

public class ShiftCommand extends Command {
	boolean highGear;
	
	public ShiftCommand(boolean highGear) {
		this.highGear = highGear;
    	requires(Robot.drive);
	}

	@Override
	protected void initialize() {
		Robot.drive.ShiftGear(highGear);
	}

	@Override
	protected void execute() {
	}

	@Override
	protected boolean isFinished() {
		return true;
	}

	@Override
	protected void end() {
		// TODO Auto-generated method stub

	}

	@Override
	protected void interrupted() {
		// TODO Auto-generated method stub

	}

}
