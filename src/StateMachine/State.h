/*
 * State.h
 *
 *  Created on: Oct 5, 2015
 *      Author: Kyle
 */

#ifndef SRC_STATEMACHINE_STATE_H_
#define SRC_STATEMACHINE_STATE_H_

#include <string>

namespace Citrus
{

class State
{
  public:
	State(std::string name);

	/**
	 * Called once when the state begins
	 */
	virtual void Start() = 0;

	/**
	 * Called repeatedly while the state is executing
	 * @return True if finished
	 */
	virtual bool Execute() = 0;

	/**
	 * Called once when the state exits
	 */
	virtual void End() = 0;

	/**
	 * @return The name of the next state, or an empty string (default) to advance to the next state
	 */
	virtual std::string GetNextState();
	std::string GetName();
	virtual ~State();

  protected:
	std::string name;
};

} /* namespace Citrus */

#endif /* SRC_STATEMACHINE_STATE_H_ */
