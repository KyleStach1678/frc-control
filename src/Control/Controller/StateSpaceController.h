/*
 * StateSpaceController.h
 *
 *  Created on: Sep 6, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_STATESPACECONTROLLER_H_
#define SRC_CONTROL_STATESPACECONTROLLER_H_

#include "Controller.h"
#include <Utils/Matrix.h>

namespace Citrus
{

/**
 * An implementation of Controller that uses state space feedback control and an estimator.
 * @tparam SensorSpace the size of the sensor(y) vector.
 * @tparam StateSpace the size of the state(x) vector.
 * @tparam OutputSpace the size of the output(u) vector.
 */
template <int SensorSpace, int StateSpace, int OutputSpace>
class StateSpaceController : public Controller<Vector<SensorSpace>, Vector<StateSpace>, Vector<OutputSpace>>
{
	Matrix<StateSpace, StateSpace> A;
	Matrix<StateSpace, OutputSpace> B;
	Matrix<SensorSpace, StateSpace> C;

	Matrix<OutputSpace, StateSpace> K;
	Matrix<StateSpace, InputSpace> L;

	Vector<StateSpace> x_hat;
	Vector<StateSpace> goal;

  public:
	StateSpaceController(ControlInput<Vector<SensorSpace>>& input, ControlOutput<Vector<OutputSpace>>& output) : Controller(input, output)
	{
	}

	/**
	 * Set the controller's gain matrices
	 * @param A the matrix representing unforced system dynamics
	 * @param B the matrix representing the effect of control output on the state
	 * @param C the matrix representing how state variables are translated into sensor values
	 * @param K the matrix used to calculate control outputs
	 * @param L the estimation matrix
	 */
	void SetGains(Matrix<StateSpace, StateSpace> A,
				  Matrix<StateSpace, OutputSpace> B,
				  Matrix<SensorSpace, StateSpace> C,
				  Matrix<OutputSpace, StateSpace> K,
				  Matrix<StateSpace, InputSpace> L)
	{
		this->A = A;
		this->B = B;
		this->C = C;
		this->K = K;
		this->L = L;
	}

	Vector<OutputSpace> Calculate(Vector<InputSpace> input, Time dt)
	{
		Vector<StateSpace> error = goal - input;
		Vector<OutputSpace> output = K * error;
		Vector<InputSpace> y_hat = C * x_hat;
		x_hat = x_hat + (A * x_hat + B * output) * dt + l * (input - y_hat);
		return output;
	}

	virtual ~StateSpaceController();
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_STATESPACECONTROLLER_H_ */
