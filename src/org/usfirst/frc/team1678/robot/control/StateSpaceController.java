package org.usfirst.frc.team1678.robot.control;

import org.usfirst.frc.team1678.robot.math.Matrix;

public class StateSpaceController extends Controller<Matrix, Matrix> {
	Matrix a, b, c, d, k, l;
	Matrix x_hat;
	
	Matrix tolerances;

	Matrix goal;

	public StateSpaceController(ControlSource<Matrix> source, ControlOutput<Matrix> output, Matrix a, Matrix b,
			Matrix c, Matrix d, Matrix k, Matrix l, Matrix tolerances) {
		super(source, output);
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.k = k;
		this.l = l;
		this.tolerances = tolerances;
		this.x_hat = new Matrix(a.rows);
		this.goal = new Matrix(a.rows);

		checkValidity();
	}

	public void setGoal(Matrix goal) {
		synchronized (this.goal) {
			this.goal = goal;
		}
	}

	private void checkValidity() {
		int sourceSize = c.rows;
		int stateSize = a.rows;
		int outputSize = b.cols;

		if (a.cols != stateSize) {
			System.err.println("Error in A matrix dimensions");
		}
		if (b.rows != stateSize || b.cols != outputSize) {
			System.err.println("Error in B matrix dimensions");
		}
		if (k.rows != outputSize || k.cols != stateSize) {
			System.err.println("Error in K matrix dimensions");
		}
		if (c.cols != stateSize || c.rows != sourceSize) {
			System.err.println("Error in C matrix dimensions");
		}
		if (d.rows != sourceSize || d.cols != outputSize) {
			System.err.println("Error in K matrix dimensions");
		}
		if (tolerances.rows != stateSize || tolerances.cols != 1) {
			System.err.println("Error in tolerance matrix dimensions");
		}
		if (x_hat.rows != stateSize || x_hat.cols != 1) {
			System.err.println("Error in x_hat matrix dimensions");
		}
		if (goal.rows != stateSize || goal.cols != 1) {
			System.err.println("Error in goal matrix dimensions");
		}
	}

	@Override
	protected Matrix calculate(Matrix sensorValues, double dt) {
		synchronized (this) {
			// Actuator output values
			Matrix error = goal.subtract(x_hat);
			Matrix output = k.multiply(error);

			// Observer
			Matrix y_hat = c.multiply(x_hat).add(d.multiply(output));
			// x_hat = x_hat + dt*(a*x_hat + b*u) + l*(y-y_hat);
			x_hat = x_hat
					.add(a.multiply(x_hat).add(b.multiply(output)).multiply(dt))
					.add(l.multiply(sensorValues.subtract(y_hat)));
			return output;
		}
	}

	@Override
	public boolean isFinished() {
		// TODO Auto-generated method stub
		return false;
	}

}
