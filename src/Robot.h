#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "CommandBase.h"

class Robot : public IterativeRobot
{
  private:
	Command* autonomousCommand;
	LiveWindow* lw;

  public:
	void RobotInit();

	void DisabledPeriodic();

	void AutonomousInit();

	void AutonomousPeriodic();

	void TeleopInit();

	void TeleopPeriodic();

	void TestPeriodic();
};
