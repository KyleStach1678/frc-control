/*
 * LogManager.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: Kyle
 */

#include "LogManager.h"

LogManager* LogManager::instance = new LogManager();

LogManager::LogManager()
{
	std::lock_guard<std::mutex> lock(logsMutex);
	running = true;
	runThread = std::thread([this] {
		while (running) {
			FlushLogs();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		FlushLogs();
	});
}

void LogManager::FlushLogs()
{
	std::lock_guard<std::mutex> lock(logsMutex);
	for (auto logPair : GetInstance()->logs) {
		logPair.second->FlushToFile();
	}
}

LogManager* LogManager::GetInstance()
{
	return instance;
}

void LogManager::AddLog(std::string key, Log* log)
{
	std::lock_guard<std::mutex> lock(logsMutex);
	if (logs.find(key) == logs.end()) {
		logs[key] = log;
	}
}

Log* LogManager::GetLog(std::string key)
{
	std::lock_guard<std::mutex> lock(logsMutex);
	if (logs.find(key) != logs.end()) {
		return logs[key];
	}
	return nullptr;
}

void LogManager::Stop()
{
	running = false;
	if (runThread.joinable()) {
		runThread.join();
	}
}

LogManager::~LogManager()
{
	running = false;
	if (runThread.joinable()) {
		runThread.join();
	}

	for (auto pair : logs) {
		delete pair.second;
	}
}
