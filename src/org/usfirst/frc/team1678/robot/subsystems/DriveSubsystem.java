package org.usfirst.frc.team1678.robot.subsystems;

import org.usfirst.frc.team1678.robot.RobotMap;
import org.usfirst.frc.team1678.robot.commands.TeleopDriveCommand;

import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class DriveSubsystem extends Subsystem {
	
	private RobotDrive drive;
	private DoubleSolenoid shifting;
	
	private boolean highGear = false;
	
    // Put methods for controlling this subsystem
    // here. Call these from Commands.
	public DriveSubsystem() {
		drive = new RobotDrive(RobotMap.leftDrivePorts[0], RobotMap.leftDrivePorts[1], RobotMap.rightDrivePorts[0], RobotMap.rightDrivePorts[1]);
		shifting = new DoubleSolenoid(RobotMap.lowGear, RobotMap.highGear);
	}

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
    	setDefaultCommand(new TeleopDriveCommand());
    }
    
    public void Drive(double power, double turning) {
    	drive.tankDrive(power - turning, power + turning);
    }
    
    public void ShiftGear(boolean high) {
    	highGear = high;
    	shifting.set(high ? DoubleSolenoid.Value.kForward : DoubleSolenoid.Value.kReverse);
    }

	public boolean isHighGear() {
		return highGear;
	}
}

