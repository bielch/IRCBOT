/*
 * Configuration.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "Configuration.h"

namespace ircbot {

Configuration* Configuration::mObject = 0;

Configuration::Configuration() {
	// TODO Auto-generated constructor stub

}

Configuration::~Configuration() {
	// TODO Auto-generated destructor stub
}

Configuration& Configuration::getInstance(){
	if(!mObject)
		mObject = new Configuration();

	return *mObject;
}

void Configuration::loadConfigurationFile(const std::string* pFilename){

}

} /* namespace ircbot */
