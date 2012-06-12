/*
 * Configuration.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "Configuration.h"
#include <fstream>

namespace ircbot {

Configuration* Configuration::mObject = 0;

Configuration::Configuration():mController(Controller::getInstance()) {

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
	std::ifstream file(pFilename->c_str());
	std::string line;

	if(file.is_open()){
		while(file.good()){
			getline(file, line);

			if (line[0] == '/' && line[1] == '/')
				continue;

			mController.executeCommand(&line);
		}

		file.close();
	}
}

void Configuration::loadParameter(int pVarcount, char* pValues[]){
	std::string line;

	for(int i = 0; i < pVarcount; i++){
		line = pValues[i];
		mController.executeCommand(&line);
	}
}

} /* namespace ircbot */
