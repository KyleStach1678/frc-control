/*
 * ControlOutput.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_CONTROLOUTPUT_H_
#define SRC_CONTROL_CONTROLOUTPUT_H_

namespace Citrus
{

template <typename OutputType>
class ControlOutput
{
  public:
	virtual ~ControlOutput(){};
	virtual OutputType set(OutputType value) const = 0;
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLOUTPUT_H_ */
