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
	void AddController(Updateable* controller);
	void Update();
	void RemoveController(Updateable* controller);
	void Stop();
	virtual ~ControllerUpdater();

	static ControllerUpdater* GetInstance();
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLLERUPDATER_H_ */
