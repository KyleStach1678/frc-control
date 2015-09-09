/*
 * Filter.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_FILTER_H_
#define SRC_CONTROL_FILTER_H_

#include "../Utils/unitscpp.h"

namespace Citrus
{

template <typename InputType, typename OutputType = InputType>
class Filter
{
  public:
	Filter();
	virtual ~Filter();
	virtual OutputType filter(InputType input) const = 0;
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_FILTER_H_ */
