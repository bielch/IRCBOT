/*
 * Log.h
 *
 *  Created on: 13.06.2012
 *      Author: develop
 */

#ifndef LOG_H_
#define LOG_H_

#include "Database.h"
#include <fstream>

namespace ircbot {

class Log {
public:
	static Log& getInstance();

	void logMessage(std::string* message);

	Database* mDatabase;
protected:
	Log();
	virtual ~Log();

	static Log* mObject;

	std::fstream mLogfile;
};

} /* namespace ircbot */
#endif /* LOG_H_ */
