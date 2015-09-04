package org.usfirst.frc.team1678.robot.control;

public class PIDController extends Controller<Double, Double> {
	double last;
	double integral;
	double kP, kI, kD;
	double tolerance;
	double goal;

	public PIDController(ControlSource<Double> source, ControlOutput<Double> output, double kP, double kI, double kD,
			double tolerance) {
		super(source, output);
		last = 0;
		integral = 0;
		this.kP = kP;
		this.kI = kI;
		this.kD = kD;
		this.tolerance = tolerance;
	}

	@Override
	protected boolean isFinished() {
		return Math.abs(last - goal) < tolerance;
	}

	@Override
	protected Double calculate(Double input, double dt) {
		integral += dt * input;
		double derivative = (input - last) / dt;
		double proportional = input;
		last = input;
		return kP * proportional + kI * integral + kD * derivative;
	}

	public void setGoalState(double goal) {
		this.goal = goal;
	}
}
