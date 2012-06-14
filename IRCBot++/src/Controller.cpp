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
	for (unsigned int i = 0; i < mConnection.size(); i++)
		mConnection[i]->leaveServer();
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
	std::vector<std::string> parts = split(*pCommand, ' ');
	std::string message = "No such command.";
	std::stringstream messagestream;

	context->pConnection->mlastCommandOrigin = *origin;

	if (parts.size() > 0) {

		DEBUG("command: " << parts[0]);

		if (parts.size() >= 2)
			DEBUG("payload: " << parts[1]);

		if (parts[0].compare("log") == 0) {
			if (parts.size() == 2) {

				if (parts[1].compare("0") == 0) {
					messagestream << "log disabled.";
					Configuration::getInstance().mLog = false;
				}

				if (parts[1].compare("1") == 0) {
					messagestream << "log enabled.";
					Configuration::getInstance().mLog = true;
				}
			} else {
				messagestream << "Invalid use of command log.";
			}
		}

		if (parts[0].compare("nickname") == 0) {
			if (parts.size() == 2) {
				messagestream << "Changed nickname to: " << parts[1];

				removeFrontWhitespaces(parts[1]);
				context->pConnection->changeNickname(&parts[1]);
			} else {
				messagestream << "Invalid use of command nickname.";
			}
		}

		if (parts[0].compare("lastseen") == 0) {
			if (parts.size() == 2) {
				removeFrontWhitespaces(parts[1]);

				messagestream << "Lastseen " << parts[1] << " " << Log::getInstance().mDatabase->getUser(&parts[1]);
			} else {
				messagestream << "Invalid use of command lastseen.";
			}
		}

		if (parts[0].compare("jchannel") == 0) {
			if (parts.size() == 2) {
				removeFrontWhitespaces(parts[1]);
				messagestream << "joined channel: " << parts[1];

				context->pConnection->joinChannel(&parts[1]);
			} else if (parts.size() == 3) {
				removeFrontWhitespaces(parts[1]);
				messagestream << "joined channel: " << parts[1] << " on server: " << parts[2];

				for (unsigned int i = 0; i < mConnection.size(); i++)
					if (i == (unsigned int) atoi(parts[2].c_str()))
						mConnection[i]->joinChannel(&parts[1]);

				context->pConnection->joinChannel(&parts[1]);
			} else {
				messagestream << "Invalid use of command jchannel.";
			}
		}

		if (parts[0].compare("lchannel") == 0) {
			if (parts.size() == 2) {

				removeFrontWhitespaces(parts[1]);
				messagestream << "leave channel: " << parts[1];

				context->pConnection->leaveChannel(&parts[1]);
			} else if (parts.size() == 3) {
				removeFrontWhitespaces(parts[1]);
				messagestream << "leave channel: " << parts[1] << " on server: " << parts[2];

				for (unsigned int i = 0; i < mConnection.size(); i++)
					if (i == (unsigned int) atoi(parts[2].c_str()))
						mConnection[i]->joinChannel(&parts[1]);

				context->pConnection->leaveChannel(&parts[1]);
			} else {
				messagestream << "Invalid use of command lchannel.";
			}
		}

		if (parts[0].compare("jserver") == 0) {
			if (parts.size() == 2) {

				removeFrontWhitespaces(parts[1]);
				messagestream << "join server: " << parts[1];

				joinServer(&parts[1], 6665, &Configuration::getInstance().mNickname);
			} else if (parts.size() == 3) {
				removeFrontWhitespaces(parts[1]);
				messagestream << "join server " << parts[1] << " on port " << parts[2];

				joinServer(&parts[1], atoi(parts[2].c_str()), &Configuration::getInstance().mNickname);
			} else if (parts.size() == 4) {
				removeFrontWhitespaces(parts[1]);
				messagestream << "join server " << parts[1] << " on port " << parts[2] << " with nickname: " << parts[3];

				joinServer(&parts[1], atoi(parts[2].c_str()), &parts[3]);
			} else {
				messagestream << "Invalid use of command lchannel.";
			}
		}

		if (parts[0].compare("lserver") == 0) {
			if (parts.size() == 1) {
				context->pConnection->leaveServer();
			} else if (parts.size() == 2) {

				removeFrontWhitespaces(parts[1]);

				messagestream << "unable to find server.";

				for (unsigned int i = 0; i < mConnection.size(); i++)
					if (parts[1].compare(mConnection[i]->mHostname) == 0 || intToString(i).compare(parts[1]) == 0) {
						messagestream.str("");
						messagestream << "leaving server: " << parts[1];
						mConnection[i]->leaveServer();
					}
			} else {
				messagestream << "Invalid use of command lchannel.";
			}
		}

		if (parts[0].compare("exit") == 0) {
			messagestream << "bye bye";

			message = messagestream.str();
			context->pConnection->sendMsg(&message, origin);

			context->pConnection->leaveServer();
		}

		if (parts[0].compare("serverlist") == 0) {
			DEBUG(mConnection.size())
			for (unsigned int i = 0; i < mConnection.size(); i++) {
				messagestream << i << ": " << mConnection[i]->mHostname << ":" << mConnection[i]->mPort << " " << mConnection[i]->mNickname;
				message = messagestream.str();
				context->pConnection->sendMsg(&message, origin);
				messagestream.str("");
			}

			messagestream.str("serverlist end.");
		}
	}
	if (messagestream.str().length() > 0)
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
