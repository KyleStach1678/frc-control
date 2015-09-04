package org.usfirst.frc.team1678.robot.control;

import edu.wpi.first.wpilibj.VictorSP;

/**
 * ControlOutput An interface to be implemented by actuators used in
 * controllers.
 * 
 * @author Kyle
 * @param <T>
 *            The variable type to feed to the actuator
 */
public interface ControlOutput<T> {
	/**
	 * A motor speed controller output
	 * 
	 * @author Kyle
	 *
	 */
	public class MotorControlOutput implements ControlOutput<Double> {
		private VictorSP speedController;

		public MotorControlOutput(VictorSP speedController) {
			this.speedController = speedController;
		}

		@Override
		public void set(Double value) {
			speedController.set(value);
		}
	}

	/**
	 * A group of control outputs that should all be fed the same value i.e.
	 * multiple motors in a drivetrain
	 * 
	 * @author Kyle
	 *
	 * @param <T>
	 */
	public class GroupControlOutput<T> implements ControlOutput<T> {
		ControlOutput<T> outputs[];

		@SafeVarargs
		public GroupControlOutput(ControlOutput<T>... outputs) {
			this.outputs = outputs;
		}

		@Override
		public void set(T value) {
			for (ControlOutput<T> output : outputs) {
				output.set(value);
			}
		}
	}

	public void set(T value);
}