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
#include "Connection.h"

namespace ircbot {

class Controller {
public:
	static Controller& getInstance();

	void startup();
	void executeCommand(std::string* pCommand);
	void joinServer(std::string* pHostname, unsigned short usPort);
	void joinChannel(std::string* pHostname, unsigned short usPort, std::string* pChannel);
	void isConnectedToServer(std::string* pHostname);
	void isConnectedToCannel(std::string* pHostname, std::string* pChannel);
	void leaveServer(std::string* pHostname);
	void leaveChannel(std::string* pHostname, std::string* pChannel);
	int getServerCount();

protected:
	Controller();
	virtual ~Controller();

	static Controller* mObject;

	std::vector<Connection*> mConnection;
	std::string mNickname;

};

} /* namespace ircbot */
#endif /* CONTROLLER_H_ */
