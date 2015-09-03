package org.usfirst.frc.team1678.robot.subsystems;

import org.usfirst.frc.team1678.robot.commands.TeleopElevatorTester;

import edu.wpi.first.wpilibj.VictorSP;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class ElevatorSubsystem extends Subsystem {
    VictorSP motor;
    // Put methods for controlling this subsystem
    // here. Call these from Commands.
    public ElevatorSubsystem() {
    	motor = new VictorSP(5);
    }

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    	setDefaultCommand(new TeleopElevatorTester());
    }
    
    public void setRaw(double value) {
    	motor.set(value);
    }
}

