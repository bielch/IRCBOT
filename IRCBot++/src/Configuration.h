/*
 * Configuration.h
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <stdio.h>
#include <string>
#include "function.h"

namespace ircbot {

class Configuration {
public:
	static Configuration& getInstance();
	void loadConfigurationFile(const std::string* pFilename);

protected:
	Configuration();
	virtual ~Configuration();

	static Configuration* mObject;
};

} /* namespace ircbot */
#endif /* CONFIGURATION_H_ */
