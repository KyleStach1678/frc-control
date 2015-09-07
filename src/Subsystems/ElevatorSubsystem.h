#ifndef ElevatorSubsystem_H
#define ElevatorSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <Utils/unitscpp.h>

class ElevatorSubsystem : public Subsystem
{
  private:
	std::unique_ptr<VictorSP> elevatorMotor;
	std::unique_ptr<Encoder> elevatorEncoder;
	std::unique_ptr<DigitalInput> hallSensor;
	std::unique_ptr<AnalogInput> bottomProx;
	std::unique_ptr<AnalogInput> topProx;

  public:
	ElevatorSubsystem();
	void InitDefaultCommand();

	void SetMotorsRaw(double value);
	void MoveToPosition(Length height);

	void ZeroEncoder();
	bool IsHallSensorTriggered();
	Length GetTopProximityDistance();
	Length GetBottomProximityDistance();
};

#endif
