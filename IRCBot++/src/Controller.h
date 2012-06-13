/*
 * Controller.h
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <string>
#include <vector>
#include "Server.h"

namespace ircbot {

class Controller {
public:
	static Controller& getInstance();

	void startup();
	void executeCommand(std::string* pCommand, ircbot_context* context = 0, std::string* origin = 0);
	void joinServer(std::string* pHostname, unsigned short usPort, std::string* pNickname);
	void joinChannel(std::string* pChannel);
	void isConnectedToServer(std::string* pHostname);
	void isConnectedToCannel(std::string* pHostname, std::string* pChannel);
	void leaveServer(std::string* pHostname);
	void leaveChannel(std::string* pHostname, std::string* pChannel);
	void removeConnection(Server* pConnection);
	int getServerCount();

protected:
	Controller();
	virtual ~Controller();

	static Controller* mObject;

	std::vector<Server*> mConnection;
};

} /* namespace ircbot */
#endif /* CONTROLLER_H_ */
