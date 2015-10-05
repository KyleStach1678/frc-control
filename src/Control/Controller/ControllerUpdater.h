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
#include <mutex>

namespace Citrus
{

class ControllerUpdater
{
	std::list<Updateable*> controllers;
	std::mutex mutex;

	static ControllerUpdater* instance;

  public:
	ControllerUpdater();
	void AddController(Updateable* controller);
	void Update();
	void RemoveController(Updateable* controller);
	virtual ~ControllerUpdater();

	static ControllerUpdater* GetInstance();
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLLERUPDATER_H_ */
