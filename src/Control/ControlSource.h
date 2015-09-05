/*
 * ControlSource.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_CONTROLSOURCE_H_
#define SRC_CONTROL_CONTROLSOURCE_H_

#include "Filter.h"

namespace Citrus
{

template <typename SourceType>
class ControlSource
{
  public:
	ControlSource(){};
	virtual ~ControlSource(){};
	virtual SourceType read() = 0;
	template <typename NewSourceType>
	FilteredControlSource<NewSourceType> filter(Filter<SourceType, NewSourceType> filter)
	{
		return FilteredControlSource<NewSourceType, SourceType>(*this, filter);
	}
};

template <typename OutputSourceType, typename InputSourceType = OutputSourceType>
class FilteredControlSource : public ControlSource<OutputSourceType>
{
	Filter<InputSourceType, OutputSourceType> filter;
	ControlSource<InputSourceType> source;

  public:
	FilteredControlSource virtual ~FilteredControlSource();
	virtual SourceType read() override
	{
		return filter.Filter(source.read());
	}
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLSOURCE_H_ */
