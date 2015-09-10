package org.usfirst.frc.team1678.robot.control;

public abstract class Controller<SourceType, OutputType> {
	private ControlSource<SourceType> source;
	private ControlOutput<OutputType> output;

	public Controller(ControlSource<SourceType> source, ControlOutput<OutputType> output) {
		this.source = source;
		this.output = output;
		ControlUpdater.addController(this);
	}

	/**
	 * Called periodically.
	 * 
	 * @param dt
	 *            The delta time, or time since the last update
	 */
	public void update(double dt) {
		SourceType sensorValue = source.read();
		OutputType actuatorValue = calculate(sensorValue, dt);
		output.set(actuatorValue);
	}

	/**
	 * To be implemented by a subclass; calculate the desired actuator values
	 * for a given input value.
	 * 
	 * @param input
	 *            The sensor value
	 * @param dt
	 *            The delta time, or time since the last update
	 * @return The output that should be applied to the actuator
	 */
	protected abstract OutputType calculate(SourceType input, double dt);

	/**
	 * To be implemented by a subclass; is the controller finished?
	 * 
	 * @return Whether or not the controller has finished
	 */
	public abstract boolean isFinished();
}
