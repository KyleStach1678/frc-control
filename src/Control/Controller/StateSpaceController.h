/*
 * StateSpaceController.h
 *
 *  Created on: Sep 6, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_STATESPACECONTROLLER_H_
#define SRC_CONTROL_STATESPACECONTROLLER_H_

#include <Control/Controller.h>
#include <Utils/Matrix.h>

namespace Citrus
{

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
