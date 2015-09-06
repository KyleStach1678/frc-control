/*
 * PIDController.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Kyle
 */

#ifndef CONTROL_PIDCONTROLLER_H_
#define CONTROL_PIDCONTROLLER_H_

#include "Controller.h"

namespace Citrus
{

class PIDController : public Controller<double, double>
{
	double kP, kI, kD;
	double integral;
	double target;

  public:
	double lastError;
	PIDController(const ControlSource<double>& source, const ControlOutput<double>& output, double kP, double kI, double kD)
		: Controller(source, output), kP(kP), kI(kI), kD(kD)
	{
		integral = 0;
		lastError = 0;
		target = 0;
	};

	void SetGoal(double target)
	{
		this->target = target;
	}

	virtual ~PIDController();
	virtual double Calculate(double input, Time dt) override;
	virtual bool IsFinished() override;
};

} /* namespace Citrus */

#endif /* CONTROL_PIDCONTROLLER_H_ */
