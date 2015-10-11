/*
 * ControllerUpdater.h
 *
 *  Created on: Sep 7, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_CONTROLLERUPDATER_H_
#define SRC_CONTROL_CONTROLLERUPDATER_H_

#include <Utils/Updateable.h>
#include <list>
#include <thread>
#include <mutex>
#include <atomic>

namespace Citrus
{

/**
 * Manages all of the robot's currently running controllers in a Singleton object. Repeatedly executes them in a separate thread until Stop() is
 * called.
 */
class ControllerUpdater
{
	Frequency tickRate = 200 / s;
	std::list<Updateable*> controllers;
	std::mutex mutex;
	std::atomic<bool> running;
	std::thread runThread;

	static ControllerUpdater* instance;

  public:
	ControllerUpdater();

	/**
	 * Add a new controller to the update list, activating it.
	 * @param controller
	 */
	void AddController(Updateable* controller);

	/**
	 * Update the controllers.
	 */
	void Update();

	/**
	 * Remove the specified controller from the update list, deactivating it.
	 * @param controller the controller to be removed
	 */
	void RemoveController(Updateable* controller);

	/**
	 * Stop the thread and exit.
	 */
	void Stop();
	virtual ~ControllerUpdater();

	/**
	 * @return the singleton ControllerUpdater instance
	 */
	static ControllerUpdater* GetInstance();
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLLERUPDATER_H_ */
