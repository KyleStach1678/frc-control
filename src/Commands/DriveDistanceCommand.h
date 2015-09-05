#ifndef DriveDistance_H
#define DriveDistance_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveDistanceCommand : public CommandBase {
  double distanceClicks;
  double offsetStart;
  double speed;

 public:
  DriveDistanceCommand(double meters, double speed = .5);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
