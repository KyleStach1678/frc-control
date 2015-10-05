/*
 * Log.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: Citrus CAD
 */

#include "Log.h"
#include <ctime>
#include <sys/time.h>
#include <sys/stat.h>
#include "LogManager.h"

std::string Log::folderPath = "./logs/" + Log::GetDateString() + "/";

std::once_flag folderCreated;

Log::Log(std::string name, std::string extension)
{
	this->name = name;
	std::call_once(folderCreated, [=]() {
		mkdir(folderPath.c_str());
		chmod(folderPath.c_str(), 0777);
	});

	std::string filePath = folderPath + name + "." + extension;

	file.open(filePath);
	LogManager::GetInstance()->AddLog(name, this);
}

Log::~Log()
{
	file.close();
}

std::string Log::GetDateString()
{
	time_t rawtime;
	tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%Y-%m-%d_%H-%M-%S", timeinfo);
	return buffer;
}

std::string Log::GetTimeString()
{
	time_t rawtime;
	tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%H-%M-%S", timeinfo);
	return buffer;
}
