/*
 * Controller.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_CONTROLLER_H_
#define SRC_CONTROL_CONTROLLER_H_

#include "ControlSource.h"
#include "ControlOutput.h"
#include <Utils/unitscpp.h>

namespace Citrus
{

template <typename SourceType, typename OutputType>
class Controller
{
	ControlSource<SourceType> source;
	ControlOutput<OutputType> output;

  public:
	Controller(ControlSource<SourceType> source, ControlOutput<OutputType> output) : source(source), output(output)
	{
	}
	virtual ~Controller();
	void Update(Time dt)
	{
		SourceType sensorValue = source.read();
		OutputType actuatorValue = calculate(sensorValue());
		output.set(actuatorValue);
	}

  protected:
	virtual OutputType Calculate(SourceType input, Time dt) = 0;
	virtual bool Start() = 0;
	virtual bool IsFinished() = 0;
	virtual bool Stop() = 0;
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLLER_H_ */
