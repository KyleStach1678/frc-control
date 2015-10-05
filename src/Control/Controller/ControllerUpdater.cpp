/*
 * ControllerUpdater.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: Kyle
 */

#include "ControllerUpdater.h"
#include "WPILib.h"

namespace Citrus
{

ControllerUpdater* ControllerUpdater::instance = new ControllerUpdater();

ControllerUpdater::ControllerUpdater()
{
	running = true;
	runThread = std::thread([this]() {
		Timer clock;
		Time delay = 1 / tickRate;
		while (running) {
			Update();

			// Ensure that the thread runs at a constant rate
			if (clock.Get() < delay.to(s)) {
				delaySeconds(delay.to(s) - clock.Get());
			}
			clock.Reset();
		}
	});
}

ControllerUpdater::~ControllerUpdater()
{
	Stop();
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

void ControllerUpdater::Stop()
{
	running = false;
	if (runThread.joinable()) {
		runThread.join();
	}
}

ControllerUpdater* Citrus::ControllerUpdater::GetInstance()
{
	return instance;
}

} /* namespace Citrus */
