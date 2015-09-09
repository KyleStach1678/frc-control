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

template <typename OutputType>
class ControlOutput
{
  public:
	virtual ~ControlOutput(){};
	virtual OutputType set(OutputType value) = 0;
};

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
	virtual double set(double value) override
	{
		speedController->Set(value);
		return value > 1 ? 1 : (value < -1 ? -1 : value);
	}
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLOUTPUT_H_ */
