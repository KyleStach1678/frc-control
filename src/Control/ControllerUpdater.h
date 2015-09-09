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
	static std::map<int, std::function<void(Time)>> controllers;

  public:
	ControllerUpdater();
	virtual ~ControllerUpdater();
	template <typename in, typename out>
	static int AddController(Citrus::Controller<in, out>* controller)
	{
		int id = (int)controller;
		controllers[id] = [&](Time dt) { controller->Update(dt); };
		return id;
	}
	static void Update()
	{
		for (auto updateFunc : controllers) {
			updateFunc.second(.05 * s);
		}
	}
	template <typename in, typename out>
	static void RemoveController(Citrus::Controller<in, out>* controller)
	{
		controllers.erase(controllers.find((int)controller));
	}
};

std::map<int, std::function<void(Time)>> ControllerUpdater::controllers = std::map<int, std::function<void(Time)>>();

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLLERUPDATER_H_ */
