/*
 * PIDController.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Kyle
 */

#ifndef CONTROL_PIDCONTROLLER_H_
#define CONTROL_PIDCONTROLLER_H_

#include "Controller.h"
#include "../Utils/unitscpp.h"

namespace Citrus
{

template <typename InputUnit, typename OutputUnit>
class PIDController : public Controller<InputUnit, OutputUnit>
{
	double kP, kI, kD;
	Units<InputUnit::AnglePow, InputUnit::LengthPow, InputUnit::TimePow + 1, InputUnit::MassPow, InputUnit::CurrentPow> integral;
	InputUnit target;
	InputUnit lastError;

  public:
	PIDController(const ControlSource<InputUnit>& source, const ControlOutput<OutputUnit>& output, double kP, double kI, double kD)
		: Controller<InputUnit, OutputUnit>(source, output), kP(kP), kI(kI), kD(kD)
	{
		integral = InputUnit(0) * s;
		lastError = InputUnit(0);
		target = InputUnit(0);
	};

	void SetGoal(InputUnit target)
	{
		this->target = target;
	}

	virtual ~PIDController();
	virtual OutputUnit Calculate(InputUnit value, Time dt) override;
	virtual bool IsFinished() override;
};

template <typename InputUnit, typename OutputUnit>
PIDController<InputUnit, OutputUnit>::~PIDController()
{
	// TODO Auto-generated destructor stub
}

template <typename InputUnit, typename OutputUnit>
OutputUnit PIDController<InputUnit, OutputUnit>::Calculate(InputUnit value, Time dt)
{
	InputUnit error = target - value;
	integral += error * dt;
	auto derivative = (error - lastError) / dt;
	return error() * kP + integral() * kI + derivative() * kD;
}

template <typename InputUnit, typename OutputUnit>
bool PIDController<InputUnit, OutputUnit>::IsFinished()
{
	return lastError < 1;
}

} /* namespace Citrus */

#endif /* CONTROL_PIDCONTROLLER_H_ */
