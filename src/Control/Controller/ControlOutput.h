/*
 * ControlOutput.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_CONTROLOUTPUT_H_
#define SRC_CONTROL_CONTROLOUTPUT_H_

#include "WPILib.h"

namespace Citrus
{

/**
 * An interface to an actuator.
 * @tparam OutputType the type of value that the actuator accepts
 */
template <typename OutputType>
class ControlOutput
{
  public:
	virtual ~ControlOutput(){};
	virtual OutputType Set(OutputType value) = 0;
};

/**
 * An output that controls a speed controller
 */
class MotorControlOutput : public ControlOutput<double>
{
	std::unique_ptr<VictorSP> speedController;

  public:
	MotorControlOutput(VictorSP* motor) : speedController(motor)
	{
	}
	virtual ~MotorControlOutput()
	{
	}
	virtual double Set(double value) override
	{
		speedController->Set(value);
		return value > 1 ? 1 : (value < -1 ? -1 : value);
	}
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLOUTPUT_H_ */
