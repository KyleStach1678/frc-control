/*
 * LogManager.h
 *
 *  Created on: Oct 4, 2015
 *      Author: Kyle
 */

#ifndef SRC_ROBOTCODE_LOGGING_LOGMANAGER_H_
#define SRC_ROBOTCODE_LOGGING_LOGMANAGER_H_

#include <thread>
#include <atomic>
#include "Log.h"

class LogManager
{
	static LogManager* instance;

	std::thread fileWriter;
	std::map<std::string, Log*> logs;
	std::mutex logsMutex;
	std::thread runThread;
	std::atomic<bool> running;
	void FlushLogs();

  public:
	LogManager();
	static LogManager* GetInstance();
	void AddLog(std::string key, Log* log);
	Log* GetLog(std::string key);
	void Stop();
	virtual ~LogManager();
};

#endif /* SRC_ROBOTCODE_LOGGING_LOGMANAGER_H_ */
