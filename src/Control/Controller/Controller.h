/*
 * Controller.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_CONTROLLER_H_
#define SRC_CONTROL_CONTROLLER_H_

#include "ControllerUpdater.h"
#include "ControlSource.h"
#include "ControlOutput.h"
#include <Utils/unitscpp.h>
#include <Utils/Updateable.h>
#include <memory>
#include <mutex>

namespace Citrus
{

template <typename SourceType, typename StateType, typename OutputType>
class Controller : public Updateable
{
	typedef std::shared_ptr<ControlSource<SourceType>> Source;
	typedef std::shared_ptr<ControlOutput<OutputType>> Output;
	Source source;
	Output output;

  public:
	Controller(Source source, Output output) : source(source), output(output)
	{
		ControllerUpdater::GetInstance()->AddController(this);
	}
	virtual ~Controller(){};
	virtual void Update(Time dt) override
	{
		std::lock_guard<std::mutex> lock(mutex);
		SourceType sensorValue = source->Read();
		OutputType actuatorValue = Calculate(sensorValue, dt);
		output->Set(actuatorValue);
	}
	void SetGoal(StateType goal)
	{
		std::lock_guard<std::mutex> lock(mutex);
		this->goal = goal;
	}
	virtual void Start(){};
	virtual bool IsFinished() = 0;
	virtual void Stop(){};

  protected:
	virtual OutputType Calculate(SourceType input, Time dt) = 0;
	StateType goal;

	std::mutex mutex;
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLLER_H_ */
