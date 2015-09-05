#ifndef ShiftCommand_H
#define ShiftCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShiftCommand : public CommandBase {
  bool highGear;

 public:
  ShiftCommand(bool highGear);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};

#endif
