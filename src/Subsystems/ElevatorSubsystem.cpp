#include "ElevatorSubsystem.h"
#include "../RobotMap.h"

ElevatorSubsystem::ElevatorSubsystem() : Subsystem("ElevatorSubsystem")
{
	elevatorMotor = std::unique_ptr<VictorSP>(new VictorSP(RobotMap::elevatorMotor));
	elevatorEncoder = std::unique_ptr<Encoder>(new Encoder(RobotMap::elevatorEncoders[0], RobotMap::elevatorEncoders[1]));
	hallSensor = std::unique_ptr<DigitalInput>(new DigitalInput(RobotMap::elevatorHallSensor));
	bottomProx = std::unique_ptr<AnalogInput>(new AnalogInput(RobotMap::bottomElevatorProximity));
	topProx = std::unique_ptr<AnalogInput>(new AnalogInput(RobotMap::topElevatorProximity));
}

void ElevatorSubsystem::InitDefaultCommand()

{
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void ElevatorSubsystem::SetMotorsRaw(double value)
{
	elevatorMotor->Set(value);
}

void ElevatorSubsystem::MoveToPosition(Length height)
{
}

void ElevatorSubsystem::ZeroEncoder()
{
	elevatorEncoder->Reset();
}

bool ElevatorSubsystem::IsHallSensorTriggered()
{
	// Test
	return hallSensor->Get();
}

Length ElevatorSubsystem::GetTopProximityDistance()
{
	return 0 * m;
}

Length ElevatorSubsystem::GetBottomProximityDistance()
{
	return 0 * m;
}
