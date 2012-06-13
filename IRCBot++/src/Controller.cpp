/*
 * Controller.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "Controller.h"
#include "Configuration.h"
#include "function.h"
#include "debug.h"
#include <cstdlib>

namespace ircbot {

Controller* Controller::mObject = 0;

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

Controller& Controller::getInstance() {
	if (!mObject)
		mObject = new Controller();

	return *mObject;
}

int Controller::getServerCount()  {
	return mConnection.size();
}

void Controller::joinServer( std::string* pHostname, unsigned short usPort) {
	mConnection.push_back(new Connection(pHostname, usPort, &mNickname));
}

void Controller::joinChannel(std::string* pHostname, unsigned short usPort, std::string* pChannel) {
	for(unsigned int i = 0; i < mConnection.size(); i++){
		if(mConnection.at(i)->mHostname.compare(*pHostname) == 0){
			//mConnection.at(i)->
		}
	}
}

void Controller::isConnectedToServer( std::string* pHostname)  {
}

void Controller::isConnectedToCannel( std::string* pHostname,  std::string* pChannel)  {
}

void Controller::leaveServer( std::string* pHostname) {
}

void Controller::leaveChannel( std::string* pHostname,  std::string* pChannel)  {
}

void Controller::startup() {
	Configuration& config = Configuration::getInstance();

	for (unsigned int i = 0; i < config.mData.size(); i++) {
		if (config.mData.at(i)->dChannel.size() == 0) {
			joinServer(&config.mData.at(i)->dHostname, config.mData.at(i)->dPort);
		} else {
			for (unsigned int j = 0; j < config.mData.at(i)->dChannel.size(); j++)
				joinChannel(&config.mData.at(i)->dHostname, config.mData.at(i)->dPort, config.mData.at(i)->dChannel.at(j));
		}
	}
}

void Controller::executeCommand(std::string* pCommand) {
	size_t equal;
	std::string command;
	std::string payload;

	equal = pCommand->find('=');
	if (equal == std::string::npos)
		equal = pCommand->find(' ');

	if (equal != std::string::npos) {
		command = pCommand->substr(0, int(equal));
		payload = pCommand->substr(int(equal), pCommand->size() - int(equal));

		DEBUG("command: " << command << " payload: " << payload);

		removeWhitespaces(command);

		if (pCommand->compare(0, 6, "server") || pCommand->compare(0, 10, "joinserver")) {
			equal = payload.find(':');
			if (equal != std::string::npos) {
				joinServer(&payload, (unsigned short) atoi(payload.substr(int(equal), payload.size() - int(equal)).c_str()));
			}
		}

	}
}
} /* namespace ircbot */
