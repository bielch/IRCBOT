/*
 * Log.cpp
 *
 *  Created on: 13.06.2012
 *      Author: develop
 */

#include "Log.h"
#include "Configuration.h"
#include "debug.h"
#include <stdlib.h>
#define LOG_FILE "./log/log.log"

namespace ircbot {

Log* Log::mObject = 0;

Log::Log() {
	system("mkdir ./log/");

	mLogfile.open(LOG_FILE, std::fstream::in | std::fstream::out | std::fstream::app);

	if (!mLogfile.is_open()) {
		DEBUG("Logfile konnte nicht geöffnet werden.");
	}

	mDatabase = new Database();
}

Log::~Log() {
	delete mDatabase;

	if (mLogfile.is_open())
		mLogfile.close();
}

void Log::logMessage(std::string* message) {
	if (Configuration::getInstance().mLog) {
		mLogfile << *message << std::endl;
		mDatabase->logx(message);
	}
}

Log& Log::getInstance() {
	DEBUG("getInstance");

	if (!mObject) {
		DEBUG("log = 0")
		mObject = new Log();
	}

	return *mObject;
}

} /* namespace ircbot */
