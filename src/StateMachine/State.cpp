/*
 * State.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: Kyle
 */

#include <StateMachine/State.h>

namespace Citrus
{

State::State(std::string name)
{
	this->name = name;
}

std::string State::GetNextState()
{
	return "";
}

std::string State::GetName()
{
	return name;
}

State::~State()
{
	// TODO Auto-generated destructor stub
}

} /* namespace Citrus */
