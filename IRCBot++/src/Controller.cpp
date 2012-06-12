/*
 * Controller.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "Controller.h"
#include "function.h"

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

int Controller::getServerCount() const {
	return mServer.size();
}

void Controller::joinServer(const std::string* pHostname) {
}
void Controller::joinChannel(const std::string* pHostname,
		const std::string* pChannel) const {
}
void Controller::isConnectedToServer(const std::string* pHostname) const {
}
void Controller::isConnectedToCannel(const std::string* pHostname,
		const std::string* pChannel) const {
}
void Controller::leaveServer(const std::string* pHostname) {
}
void Controller::leaveChannel(const std::string* pHostname,
		const std::string* pChannel) const {
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

		removeWhitespaces(command);

		switch (command.size()) {
		case 6:
			if (pCommand->compare(0, 6, "server"))
				joinServer(&payload);
			break;
		case 10:
			if (pCommand->compare(0, 10, "joinserver"))
				joinServer(&payload);
			break;

		default:
			//command not found
			break;
		}
	}
}
} /* namespace ircbot */
