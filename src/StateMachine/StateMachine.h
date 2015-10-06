/*
 * StateMachine.h
 *
 *  Created on: Oct 5, 2015
 *      Author: Kyle
 */

#ifndef SRC_STATEMACHINE_STATEMACHINE_H_
#define SRC_STATEMACHINE_STATEMACHINE_H_

#include <vector>
#include <memory>
#include "State.h"

namespace Citrus
{

class StateMachine
{
	std::vector<std::shared_ptr<State>> states;
	std::vector<std::shared_ptr<State>>::iterator currentState;

  public:
	StateMachine();
	template <typename T, typename... Args>
	void AttachState(Args&&... __args)
	{
		states.push_back(std::make_shared<T>(__args...));
	}
	void Update();
	virtual ~StateMachine();
};

} /* namespace Citrus */

#endif /* SRC_STATEMACHINE_STATEMACHINE_H_ */
