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
#include <memory>
#include <Utils/Updateable.h>

namespace Citrus
{

template <typename SourceType, typename StateType, typename OutputType>
class Controller : public Updateable
{
	std::shared_ptr<ControlSource<SourceType>> source;
	std::shared_ptr<ControlOutput<OutputType>> output;

  public:
	Controller(std::shared_ptr<ControlSource<SourceType>> source, std::shared_ptr<ControlOutput<OutputType>> output) : source(source), output(output)
	{
	}
	virtual ~Controller(){};
	virtual void Update(Time dt) override
	{
		SourceType sensorValue = source->Read();
		OutputType actuatorValue = Calculate(sensorValue, dt);
		output->Set(actuatorValue);
	}
	void SetGoal(StateType goal)
	{
		this->goal = goal;
	}
	virtual void Start(){};
	virtual bool IsFinished() = 0;
	virtual void Stop(){};

  protected:
	virtual OutputType Calculate(SourceType input, Time dt) = 0;
	StateType goal;
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLLER_H_ */
