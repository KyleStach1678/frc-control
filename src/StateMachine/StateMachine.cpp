/*
 * StateMachine.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: Kyle
 */

#include "StateMachine.h"
#include <Logging/TextLog.h>

namespace Citrus
{

StateMachine::StateMachine()
{
	currentState = states.begin();
}

void StateMachine::Update()
{
	bool finished = (*currentState)->Execute();
	if (finished) {
		std::string next = (*currentState)->GetNextState();

		auto it(currentState);
		for (; it != currentState && !((*it)->GetName() == next || (*it)->GetName() == "") && currentState != states.end(); it++) {
		}

		(*currentState)->End();

		if (it == currentState) {
			TextLog::WriteToLog("general", "State " + next + " does not exist", "STATEMACHINE", CODE_STAMP);
		} else if (it == states.end()) {
			// The state machine is done!
		} else {
			currentState = it;
			(*currentState)->Start();
		}
	}
}

StateMachine::~StateMachine()
{
	// TODO Auto-generated destructor stub
}

} /* namespace Citrus */
