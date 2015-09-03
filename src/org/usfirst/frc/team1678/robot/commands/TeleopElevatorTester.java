package org.usfirst.frc.team1678.robot.commands;

import org.usfirst.frc.team1678.robot.OI;
import org.usfirst.frc.team1678.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;

public class TeleopElevatorTester extends Command {
	
	public TeleopElevatorTester() {
		requires(Robot.elevator);
	}
	
	@Override
	protected void initialize() {
		// TODO Auto-generated method stub

	}

	@Override
	protected void execute() {
		Robot.elevator.setRaw(OI.getElevator());
	}

	@Override
	protected boolean isFinished() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	protected void end() {
		Robot.elevator.setRaw(0);
	}

	@Override
	protected void interrupted() {
		// TODO Auto-generated method stub

	}

}
