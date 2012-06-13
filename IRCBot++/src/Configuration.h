/*
 * Configuration.h
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "Controller.h"
#include "structs.h"
#include <stdio.h>
#include <vector>
#include <string>

namespace ircbot {

class Configuration {
	friend class Controller;
public:
	static Configuration& getInstance();
	void loadConfigurationFile(const std::string* pFilename);
	void loadParameter(int pVarcount, char* pValues[]);

protected:
	Configuration();
	virtual ~Configuration();

	static Configuration* mObject;

	Controller& mController;
	std::string mNickname;
	std::vector<connection_context*> mData;
	bool mDeamonize;
	bool mLog;
};

} /* namespace ircbot */
#endif /* CONFIGURATION_H_ */
