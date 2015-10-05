/*
 * ControllerUpdater.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: Kyle
 */

#include "ControllerUpdater.h"

namespace Citrus
{

ControllerUpdater* ControllerUpdater::instance = new ControllerUpdater();

ControllerUpdater::ControllerUpdater()
{
}

void ControllerUpdater::AddController(Updateable* controller)
{
	std::lock_guard<std::mutex> lock(mutex);
	controllers.push_back(controller);
}

void ControllerUpdater::RemoveController(Updateable* controller)
{
	std::lock_guard<std::mutex> lock(mutex);
	controllers.remove(controller);
}

void ControllerUpdater::Update()
{
	std::lock_guard<std::mutex> lock(mutex);
	for (auto controller : controllers) {
		controller->Update(.05 * s);
	}
}

ControllerUpdater::~ControllerUpdater()
{
}

ControllerUpdater* Citrus::ControllerUpdater::GetInstance()
{
	return instance;
}

} /* namespace Citrus */
