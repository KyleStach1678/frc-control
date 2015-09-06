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

template <typename OutputSourceType, typename InputSourceType = OutputSourceType>
class FilteredControlSource;

template <typename SourceType>
class ControlSource
{
  public:
	ControlSource(){};
	virtual ~ControlSource(){};
	virtual SourceType read() const = 0;
	template <typename NewSourceType>
	FilteredControlSource<NewSourceType> filter(Filter<SourceType, NewSourceType> filter) const
	{
		return FilteredControlSource<NewSourceType, SourceType>(*this, filter);
	}
};

template <typename OutputSourceType, typename InputSourceType>
class FilteredControlSource : public ControlSource<OutputSourceType>
{
	Filter<InputSourceType, OutputSourceType> filter;
	ControlSource<InputSourceType> source;

  public:
	virtual ~FilteredControlSource();
	virtual InputSourceType read() const override
	{
		return filter.Filter(source.read());
	}
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLSOURCE_H_ */
