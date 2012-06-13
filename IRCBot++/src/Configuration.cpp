/*
 * Configuration.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "Configuration.h"
#include "debug.h"
#include <fstream>

namespace ircbot {

Configuration* Configuration::mObject = 0;

Configuration::Configuration() :
		mController(Controller::getInstance()), mNickname("IRCBot++"), mDeamonize(false), mLog(false) {

}

Configuration::~Configuration() {
	// TODO Auto-generated destructor stub
}

Configuration& Configuration::getInstance() {
	if (!mObject)
		mObject = new Configuration();

	return *mObject;
}

void Configuration::loadConfigurationFile(const std::string* pFilename) {
	if (mData.size() == 0) {

		std::ifstream file(pFilename->c_str());
		std::string line;

		if (file.is_open()) {
			while (file.good()) {
				getline(file, line);

				if (line[0] == '/' && line[1] == '/')
					continue;

				mController.executeCommand(&line);
			}

			file.close();
		}
	}
}

void Configuration::loadParameter(int pVarcount, char* pValues[]) {
	std::string line;

	for (int i = 0; i < pVarcount; i++) {

		line = pValues[i];

		if (line.compare(0, 2, "-s") == 0 && line.size() == 2 && i + 1 < pVarcount) {
			mData.push_back(new server_context);
			mData.back()->dHostname = pValues[i + 1];
		} else if (line.compare(0, 2, "-c") == 0 && line.size() == 2 && i + 1 < pVarcount) {
			mData.back()->dChannel.push_back(new std::string(pValues[i + 1]));
		} else if (line.compare(0, 2, "-p") == 0 && line.size() == 2 && i + 1 < pVarcount) {
			mData.back()->dPort = atoi(pValues[i + 1]);
		} else if (line.compare(0, 7, "-deamon") == 0 && line.size() == 7) {
			mDeamonize = true;
		} else if (line.compare(0, 4, "-log") == 0 && line.size() == 4) {
			mLog = true;
		}
	}
}

} /* namespace ircbot */
