/*
 * CSVLog.h
 *
 *  Created on: Oct 2, 2015
 *      Author: Kyle
 */

#ifndef SRC_ROBOTCODE_LOGGING_CSVLOG_H_
#define SRC_ROBOTCODE_LOGGING_CSVLOG_H_

#include "Log.h"
#include <vector>

class CSVLog : public Log
{
	std::stringstream buffer;
	std::vector<std::pair<std::string, std::string>> entries;

  public:
	CSVLog(std::string filename, std::vector<std::string> keys);
	virtual void Write(std::string key, std::string value);
	virtual void EndLine();
	virtual std::string& operator[](std::string key);

	virtual void FlushToFile() override;
	virtual std::string GetExtension() const override;

	static void WriteToLog(std::string log, std::string key, std::string value);
	virtual ~CSVLog();
};

#endif /* SRC_ROBOTCODE_LOGGING_CSVLOG_H_ */
