package org.usfirst.frc.team1678.robot;

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
public class RobotMap {
	public static final int lowGear = 1;
	public static final int highGear = 2;

	public static final int leftDrivePorts[] = { 1, 8 };
	public static final int rightDrivePorts[] = { 2, 7 };
	public static final int elevatorMotor = 5;

	public static final int leftDriverStick = 0;
	public static final int rightDriverStick = 1;

	public static final int elevatorEncoders[] = { 14, 15 };
	public static final int leftDriveEncoders[] = { 12, 13 };
	public static final int rightDriveEncoders[] = { 10, 11 };

	public static final int elevatorHallSensor = 0;
	
	public static final int bottomElevatorProximity = 0;
	public static final int topElevatorProximity = 1;
}
