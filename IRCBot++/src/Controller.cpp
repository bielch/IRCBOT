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

int Controller::getServerCount() {
	return mConnection.size();
}

void Controller::joinServer(std::string* pHostname, unsigned short usPort, std::string* pNickname) {
	mConnection.push_back(new Connection(pHostname, usPort, pNickname));
}

void Controller::joinChannel(std::string* pHostname, unsigned short usPort, std::string* pChannel, std::string* pNickname) {
	mConnection.push_back(new Connection(pHostname, usPort, pNickname, pChannel));
}

void Controller::isConnectedToServer(std::string* pHostname) {
}

void Controller::isConnectedToCannel(std::string* pHostname, std::string* pChannel) {
}

void Controller::leaveServer(std::string* pHostname) {
}

void Controller::leaveChannel(std::string* pHostname, std::string* pChannel) {
}

void Controller::startup() {
	Configuration& config = Configuration::getInstance();

	for (unsigned int i = 0; i < config.mData.size(); i++) {
		if (config.mData.at(i)->dChannel.size() == 0) {
			joinServer(&config.mData.at(i)->dHostname, config.mData.at(i)->dPort, &config.mData.at(i)->dNickname);
		} else {
			joinChannel(&config.mData.at(i)->dHostname, config.mData.at(i)->dPort, &config.mData.at(i)->dChannel, &config.mData.at(i)->dNickname);
		}
	}
}

void Controller::executeCommand(std::string* pCommand, ircbot_context* context) {
	size_t equal;
	std::string command;
	std::string payload;

	removeFrontWhitespaces(*pCommand);

	equal = pCommand->find('=');
	if (equal == std::string::npos)
		equal = pCommand->find(' ');

	if (equal != std::string::npos) {
		command = pCommand->substr(0, int(equal));
		payload = pCommand->substr(int(equal), pCommand->size() - int(equal));

		removeWhitespaces(command);

		DEBUG("command: " << command << " payload: " << payload);

		if (command.compare("log") == 0) {
			removeWhitespaces(payload);

			if (payload.compare("0") == 0)
				Configuration::getInstance().mLog = false;

			if (payload.compare("1") == 0)
				Configuration::getInstance().mLog = true;
		}

		if(command.compare("nickname") == 0){
			context->pConnection->
		}

	}
}

void Controller::removeConnection(Connection* pConnection) {
	for (unsigned int i = 0; i < mConnection.size(); i++)
		if (mConnection.at(i) == pConnection) {
			mConnection.erase(mConnection.begin() + i);

			delete pConnection;
		}
}
} /* namespace ircbot */
