package org.usfirst.frc.team1678.robot.subsystems;

import org.usfirst.frc.team1678.robot.Constants;
import org.usfirst.frc.team1678.robot.RobotMap;
import org.usfirst.frc.team1678.robot.commands.TeleopElevatorTester;
import org.usfirst.frc.team1678.robot.control.ControlOutput;
import org.usfirst.frc.team1678.robot.control.ControlSource;
import org.usfirst.frc.team1678.robot.control.PIDController;

import edu.wpi.first.wpilibj.AnalogInput;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.VictorSP;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 * The elevator on the robot, used for lifting totes
 * 
 * @author Kyle
 *
 */
public class ElevatorSubsystem extends Subsystem {
	private ControlOutput.MotorControlOutput motor;
	private ControlSource.EncoderControlSource heightEncoder;
	private DigitalInput hallSensor;

	private PIDController positionController;
	private AnalogInput bottomProx;
	private AnalogInput topProx;

	public ElevatorSubsystem() {
		motor = new ControlOutput.MotorControlOutput(new VictorSP(RobotMap.elevatorMotor));
		heightEncoder = new ControlSource.EncoderControlSource(
				new Encoder(RobotMap.elevatorEncoders[0], RobotMap.elevatorEncoders[1]));
		positionController = new PIDController(heightEncoder, motor, .0001, 0, 0, 3);
		hallSensor = new DigitalInput(RobotMap.elevatorHallSensor);

		bottomProx = new AnalogInput(RobotMap.bottomElevatorProximity);
		topProx = new AnalogInput(RobotMap.topElevatorProximity);
	}

	/*
	 * These functions perform operations critical to the subsystem
	 */

	public void setRaw(double value) {
		motor.set(value);
	}

	public void moveToPosition(double height) {
		double targetPosition = height * Constants.meters_to_elev_encoders;
		positionController.setGoalState(targetPosition);
	}

	/*
	 * Utilities - these functions perform trivial operations such as getting
	 * and setting
	 */

	public void resetEncoderZero() {
		heightEncoder.reset();
	}

	public boolean isHallEffectTriggered() {
		return hallSensor.get();
	}
	
	public double getBottomProximityDistance() {
		return bottomProx.getVoltage();
	}
	
	public double getTopProximityDistance() {
		return topProx.getVoltage();
	}

	/*
	 * Boilerplate - the required functions for a Subsystem to operate
	 */

	public void initDefaultCommand() {
		// Set the default command for a subsystem here.
		setDefaultCommand(new TeleopElevatorTester());
	}
}
