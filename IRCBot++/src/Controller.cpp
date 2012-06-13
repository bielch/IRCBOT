/*
 * Controller.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "Controller.h"
#include "Configuration.h"
#include "Log.h"
#include "function.h"
#include "debug.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>

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
	mConnection.push_back(new Server(pHostname, usPort, pNickname));
}

void Controller::joinChannel(std::string* pChannel) {
	if (mConnection.size() != 0)
		mConnection.back()->joinChannel(pChannel);
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
		joinServer(&config.mData[i]->dHostname, config.mData[i]->dPort, &config.mData[i]->dNickname);

		for (unsigned int j = 0; j < config.mData[i]->dChannel.size(); j++)
			joinChannel(config.mData[i]->dChannel[j]);
	}
}

void Controller::executeCommand(std::string* pCommand, ircbot_context* context, std::string* origin) {
	size_t equal;
	std::string command;
	std::string payload;
	std::string message;
	std::stringstream messagestream;

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

			if (payload.compare("0") == 0) {
				messagestream << "log disabled.";
				Configuration::getInstance().mLog = false;
			}

			if (payload.compare("1") == 0) {
				messagestream << "log enabled.";
				Configuration::getInstance().mLog = true;
			}
		}

		if (command.compare("nickname") == 0) {
			messagestream << "Changed nickname to: " << payload;

			removeFrontWhitespaces(payload);
			context->pConnection->changeNickname(&payload);
		}

		if (command.compare("lastseen") == 0) {
			removeFrontWhitespaces(payload);

			messagestream << "Lastseen " << payload << " " << Log::getInstance().mDatabase->getUser(&payload);
		}

		if (command.compare("jchannel") == 0) {
			removeFrontWhitespaces(payload);
			messagestream << "joined channel: " << payload;

			context->pConnection->joinChannel(&payload);
		}
	}
	message = messagestream.str();
	context->pConnection->sendMsg(&message, origin);
}

void Controller::removeConnection(Server* pConnection) {
	for (unsigned int i = 0; i < mConnection.size(); i++)
		if (mConnection[i] == pConnection) {
			mConnection.erase(mConnection.begin() + i);

			delete pConnection;
		}
}
} /* namespace ircbot */
