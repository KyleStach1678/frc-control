package org.usfirst.frc.team1678.robot;

import org.usfirst.frc.team1678.robot.commands.ShiftCommand;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.buttons.JoystickButton;

/**
 * This class is the glue that binds the controls on the physical operator
 * interface to the commands and command groups that allow control of the robot.
 */
public class OI {
	private static Joystick driverLeft = new Joystick(RobotMap.leftDriverStick);
	private static Joystick driverRight = new Joystick(RobotMap.rightDriverStick);
	private static JoystickButton shiftLow = new JoystickButton(driverLeft, 3);
	private static JoystickButton shiftHigh = new JoystickButton(driverRight, 3);
	
	static {
		shiftLow.whenPressed(new ShiftCommand(false));
		shiftHigh.whenPressed(new ShiftCommand(true));
	}
	
	public static double getForwardPower() {
		return driverLeft.getRawAxis(1);
	}
	
	public static double getTurning() {
		return driverRight.getRawAxis(0);
	}
}

