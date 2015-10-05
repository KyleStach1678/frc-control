/*
 * TextLog.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: Kyle
 */

#include "TextLog.h"
#include "LogManager.h"

TextLog::TextLog(std::string name) : Log(name, GetExtension())
{
	// TODO Auto-generated constructor stub
}

std::string TextLog::GetExtension() const
{
	return "log";
}

TextLog::~TextLog()
{
	// TODO Auto-generated destructor stub
}

void TextLog::Write(std::string message, std::string category, std::string codeStamp)
{
	std::string fullMessage = "[" + category + "@" + Log::GetTimeString() + "] " + message + codeStamp + " in thread ";
	std::thread::id tid = std::this_thread::get_id();

	std::lock_guard<std::mutex> lock(mutex);
	buffer << fullMessage << tid << "\n";
}

void TextLog::WriteToLog(std::string log, std::string message, std::string category, std::string codeStamp)
{
	((TextLog*)LogManager::GetInstance()->GetLog(log))->Write(message, category, codeStamp);
}

void TextLog::FlushToFile()
{
	std::lock_guard<std::mutex> lock(mutex);
	file << buffer.str();
	file.flush();
	std::cout << buffer.str() << std::endl;
	buffer.str(std::string());
}
