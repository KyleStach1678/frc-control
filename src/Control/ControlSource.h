/*
 * ControlSource.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_CONTROLSOURCE_H_
#define SRC_CONTROL_CONTROLSOURCE_H_

#include "WPILib.h"
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
	virtual SourceType Read() = 0;
	template <typename NewSourceType>
	FilteredControlSource<NewSourceType, SourceType> filter(Filter<SourceType, NewSourceType>& filter) const
	{
		return FilteredControlSource<NewSourceType, SourceType>(*this, filter);
	}
};

template <typename OutputSourceType, typename InputSourceType>
class FilteredControlSource : public ControlSource<OutputSourceType>
{
	const Filter<InputSourceType, OutputSourceType>& filter;
	ControlSource<InputSourceType>& source;

  public:
	FilteredControlSource(ControlSource<InputSourceType>& source, Filter<InputSourceType, OutputSourceType>& filter)
	{
		this->filter = filter;
		this->source = source;
	}
	virtual ~FilteredControlSource();
	virtual OutputSourceType Read() override
	{
		return filter.Filter(source.read());
	}
};

class EncoderControlSource : public ControlSource<double>
{
	std::unique_ptr<Encoder> enc;
	double offset;

  public:
	EncoderControlSource(Encoder* enc) : enc(enc)
	{
		offset = enc->Get();
	}
	virtual ~EncoderControlSource()
	{
	}
	virtual double Read() override
	{
		return enc->Get() - offset;
	}
	void Reset()
	{
		offset = enc->Get();
	}
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_CONTROLSOURCE_H_ */
