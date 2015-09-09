#include "ElevatorSubsystem.h"
#include "../RobotMap.h"

ElevatorSubsystem::ElevatorSubsystem() : Subsystem("ElevatorSubsystem")
{
	elevatorMotor = std::make_shared<Citrus::MotorControlOutput>(new VictorSP(RobotMap::elevatorMotor));
	elevatorEncoder = std::make_shared<Citrus::EncoderControlSource>(new Encoder(RobotMap::elevatorEncoders[0], RobotMap::elevatorEncoders[1]));
	hallSensor = std::unique_ptr<DigitalInput>(new DigitalInput(RobotMap::elevatorHallSensor));
	bottomProx = std::unique_ptr<AnalogInput>(new AnalogInput(RobotMap::bottomElevatorProximity));
	topProx = std::make_unique<AnalogInput>(RobotMap::topElevatorProximity);
	elevatorController = std::make_unique<Citrus::PIDController>(elevatorEncoder, elevatorMotor, .05, .001, .001);
}

void ElevatorSubsystem::InitDefaultCommand()

{
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void ElevatorSubsystem::SetMotorsRaw(double value)
{
	elevatorMotor->set(value);
}

void ElevatorSubsystem::MoveToPosition(Length height)
{
	elevatorController->SetGoal((height / click)());
	elevatorController->Start();
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
