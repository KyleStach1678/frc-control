/*
 * ControllerUpdater.h
 *
 *  Created on: Sep 7, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_CONTROLLERUPDATER_H_
#define SRC_CONTROL_CONTROLLERUPDATER_H_

#include "Controller.h"
#include <map>

namespace Citrus
{

class ControllerUpdater
{
	static std::list<Updateable*> controllers;

  public:
	ControllerUpdater();
	virtual ~ControllerUpdater();
	template <typename in, typename state, typename out>
	static void AddController(Citrus::Controller<in, state, out>* controller)
	{
		controllers.push_back(controller);
	}
	static void Update()
	{
		for (auto controller : controllers) {
			controller->Update(.05 * s);
		}
	}
	template <typename in, typename state, typename out>
	static void RemoveController(Citrus::Controller<in, state, out>* controller)
	{
		controllers.remove(controller);
	}
};

std::list<Updateable*> ControllerUpdater::controllers;

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLLERUPDATER_H_ */
