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
#include "../Utils/unitscpp.h"

namespace Citrus
{

template <typename SourceType, typename OutputType>
class Controller
{
	const ControlSource<SourceType>& source;
	const ControlOutput<OutputType>& output;

  public:
	Controller(const ControlSource<SourceType>& source, const ControlOutput<OutputType>& output) : source(source), output(output)
	{
	}
	virtual ~Controller(){};
	void Update(Time dt)
	{
		SourceType sensorValue = source.read();
		OutputType actuatorValue = Calculate(sensorValue, dt);
		output.set(actuatorValue);
	}

  protected:
	virtual OutputType Calculate(SourceType input, Time dt) = 0;
	virtual void Start(){};
	virtual bool IsFinished() = 0;
	virtual void Stop(){};
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLLER_H_ */
