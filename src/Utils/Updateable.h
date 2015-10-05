/*
 * Updateable.h
 *
 *  Created on: Sep 30, 2015
 *      Author: Kyle
 */

#ifndef SRC_CONTROL_UPDATEABLE_H_
#define SRC_CONTROL_UPDATEABLE_H_

#include <Utils/unitscpp.h>

namespace Citrus
{

class Updateable
{
  public:
	virtual void Update(Time dt) = 0;
	virtual ~Updateable(){};
};

} /* namespace Citrus */

#endif /* SRC_CONTROL_UPDATEABLE_H_ */
