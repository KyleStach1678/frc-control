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

/**
 * An interface for an object that sets outputs (often actuators) in response to inputs (sensors) and setpoints or goals.
 * @tparam SourceType the type of the data provided by the source
 * @tparam StateType the type of the data used to represent the system's state, used in setting the goal state
 * @tparam OutputType the type of the data given to the output
 */
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

	/**
	 * Update the controller by calculating values via the virtual Calculate() function which is overridden by a base class
	 * @param dt delta time
	 */
	virtual void Update(Time dt) override
	{
		std::lock_guard<std::mutex> lock(mutex);
		SourceType sensorValue = source->Read();
		OutputType actuatorValue = Calculate(sensorValue, dt);
		output->Set(actuatorValue);
	}

	/**
	 * Set the controller's goal state
	 * @param goal the new goal state
	 */
	void SetGoal(StateType goal)
	{
		std::lock_guard<std::mutex> lock(mutex);
		this->goal = goal;
	}

	/**
	 * Called once to start the controller; adds the controller to the ControllerUpdater. Can be overridden but the default implementation should
	 * always be called at the beginning of the subclass's implementation.
	 */
	virtual void Start()
	{
		ControllerUpdater::GetInstance()->AddController(this);
	};

	/**
	 * Is the controller finished?
	 * @return true if the controller is done
	 */
	virtual bool IsFinished() = 0;

	/**
	 * Called once to stop the controller; removes the controller from the ControllerUpdater. Can be overridden but the default implementation should
	 * always be called at the end of the subclass's implementation.
	 */
	virtual void Stop()
	{
		ControllerUpdater::GetInstance()->RemoveController(this);
	};

  protected:
	/**
	 * Calculate the correct actuator values based on the input values to reach the desired goal state. Should be overridden by a subclass.
	 * @param input the input values from the sensors
	 * @param dt delta time
	 * @return the values to send to the actuators
	 */
	virtual OutputType Calculate(SourceType input, Time dt) = 0;
	StateType goal;

	std::mutex mutex;
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLLER_H_ */
