/*
 * CSVLog.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: Kyle
 */

#include "CSVLog.h"
#include "LogManager.h"

CSVLog::CSVLog(std::string filename, std::vector<std::string> keys) : Log(filename, GetExtension())
{
	buffer << "timestamp,";
	for (auto key = keys.begin(); key != keys.end(); key++) {
		buffer << *key;
		if (key + 1 != keys.end()) {
			buffer << ",";
		}
		this->entries.push_back(std::make_pair(*key, ""));
	}
	buffer << "\n";
}

/**
 * Write a value to a key in the csv log for the current line.
 */
void CSVLog::Write(std::string key, std::string value)
{
	for (auto entry = entries.begin(); entry != entries.end(); entry++) {
		if (entry->first == key) {
			entry->second = value;
		}
	}
}

/**
 * Begin writing values on a new line.
 */
void CSVLog::EndLine()
{
	std::lock_guard<std::mutex> lock(mutex);
	buffer << Log::GetTimeString() << ",";
	for (auto entry = entries.begin(); entry != entries.end(); entry++) {
		buffer << entry->second;
		if (entry + 1 != entries.end()) {
			buffer << ",";
		}
		entry->second = "";
	}
	buffer << "\n";
}

/**
 * Save the current data to the log.
 */
void CSVLog::FlushToFile()
{
	std::lock_guard<std::mutex> lock(mutex);
	file << buffer.str();
	file.flush();
	std::cout << buffer.str() << std::endl;
	buffer.str(std::string());
}

std::string CSVLog::GetExtension() const
{
	return "csv";
}

/**
 * Save the log to the disk.
 */
void CSVLog::WriteToLog(std::string log, std::string key, std::string value)
{
	((CSVLog*)LogManager::GetInstance()->GetLog(key))->Write(key, value);
}

std::string& CSVLog::operator[](std::string key)
{
	for (auto it = entries.begin(); it != entries.end(); it++) {
		if (it->first == key) {
			return it->second;
		}
	}
	return entries.begin()->second;
}

CSVLog::~CSVLog()
{
}
