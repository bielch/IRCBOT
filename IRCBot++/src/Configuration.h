/*
 * Configuration.h
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "Controller.h"
#include <stdio.h>
#include <string>

namespace ircbot {

class Configuration {
public:
	static Configuration& getInstance();
	void loadConfigurationFile(const std::string* pFilename);
	void loadParameter(int pVarcount, char* pValues[]);

protected:
	Configuration();
	virtual ~Configuration();

	static Configuration* mObject;
	Controller& mController;
};

} /* namespace ircbot */
#endif /* CONFIGURATION_H_ */
