#ifndef TeleopDriveCommand_H
#define TeleopDriveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TeleopDriveCommand : public CommandBase
{
  public:
	TeleopDriveCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif
