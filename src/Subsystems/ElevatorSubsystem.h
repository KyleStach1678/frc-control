#ifndef ElevatorSubsystem_H
#define ElevatorSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <Utils/unitscpp.h>
#include "../Control/PIDController.h"
#include "../Control/ControlSource.h"
#include "../Control/ControlOutput.h"

class ElevatorSubsystem : public Subsystem
{
  private:
	std::shared_ptr<Citrus::MotorControlOutput> elevatorMotor;
	std::shared_ptr<Citrus::EncoderControlSource> elevatorEncoder;
	std::unique_ptr<DigitalInput> hallSensor;
	std::unique_ptr<AnalogInput> bottomProx;
	std::unique_ptr<AnalogInput> topProx;
	std::unique_ptr<Citrus::PIDController> elevatorController;

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
