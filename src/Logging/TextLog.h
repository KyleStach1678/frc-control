/*
 * TextLog.h
 *
 *  Created on: Oct 2, 2015
 *      Author: Kyle
 */

#ifndef SRC_ROBOTCODE_LOGGING_TEXTLOG_H_
#define SRC_ROBOTCODE_LOGGING_TEXTLOG_H_

#include "Log.h"

class TextLog : public Log
{
	std::stringstream buffer;

  public:
	TextLog(std::string name);
	virtual void Write(std::string message, std::string category, std::string codeStamp);
	virtual void FlushToFile() override;
	virtual std::string GetExtension() const override;
	static void WriteToLog(std::string log, std::string message, std::string category, std::string codeStamp);
	virtual ~TextLog();
};

#endif /* SRC_ROBOTCODE_LOGGING_TEXTLOG_H_ */
