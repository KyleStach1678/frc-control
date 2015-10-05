/*
 * Log.h
 *
 *  Created on: Oct 1, 2015
 *      Author: Citrus CAD
 */

#ifndef SRC_LOGGING_LOG_H_
#define SRC_LOGGING_LOG_H_

#include <thread>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <mutex>
#include <map>

//#define LOG_VERBOSE

#ifdef LOG_VERBOSE
#define CODE_STAMP (" (at line " + std::to_string(__LINE__) + " of " + __FILE__ + " in function " + __PRETTY_FUNCTION__ + ")")
#else
#define CODE_STAMP ""
#endif

class Log
{
  protected:
	static std::string GetDateString();
	static std::string GetTimeString();

	static std::string folderPath;

	std::ofstream file;
	std::mutex mutex;
	std::string name;

  public:
	Log(std::string name, std::string extension);
	virtual void FlushToFile() = 0;
	virtual std::string GetExtension() const = 0;
	virtual ~Log();
};

#endif /* SRC_LOGGING_LOG_H_ */
