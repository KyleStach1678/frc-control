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

	// The thread runs at a constant rate, calling Update() to asynchronously update controllers
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
	// Kill the new thread when the object is destroyed
	Stop();
}

void ControllerUpdater::AddController(Updateable* controller)
{
	// Lock the mutex to prevent iterator invalidization in Update
	std::lock_guard<std::mutex> lock(mutex);
	controllers.push_back(controller);
}

void ControllerUpdater::RemoveController(Updateable* controller)
{
	// Lock the mutex to prevent iterator invalidization in Update
	std::lock_guard<std::mutex> lock(mutex);
	controllers.remove(controller);
}

void ControllerUpdater::Update()
{
	// Lock the mutex to prevent iterator invalidization
	std::lock_guard<std::mutex> lock(mutex);
	for (auto controller : controllers) {
		controller->Update(.05 * s);
	}
}

void ControllerUpdater::Stop()
{
	// Kill the thread and wait for it to join
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
