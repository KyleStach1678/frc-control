/*
 * PIDController.h
 *
 *  Created on: Sep 7, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_PIDCONTROLLER_H_
#define SRC_CONTROL_PIDCONTROLLER_H_

#include "Controller.h"

namespace Citrus
{

typedef std::shared_ptr<ControlSource<double>> PIDSourcePtr;
typedef std::shared_ptr<ControlOutput<double>> PIDOutputPtr;

class PIDController : public Controller<double, double>
{
  public:
	PIDController(PIDSourcePtr sensor, PIDOutputPtr actuator, double kP, double kI, double kD);
	virtual ~PIDController();
	virtual void Start();
	virtual bool IsFinished();
	virtual void Stop();
	void SetGoal(double goal);

  protected:
	virtual double Calculate(double input, Time dt);
	double proportional;
	double integral;
	double derivative;
	double goal;
	double kP, kI, kD;
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_PIDCONTROLLER_H_ */
