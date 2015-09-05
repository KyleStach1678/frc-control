#ifndef DriveDistance_H
#define DriveDistance_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <Utils/unitscpp.h>

class DriveDistanceCommand : public CommandBase
{
	Length distanceClicks;
	Length offsetStart;
	Velocity speed;

  public:
	DriveDistanceCommand(Length meters, Velocity speed = .5 * m / s);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
