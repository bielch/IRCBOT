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

	void executeCommand(std::string* pCommand);
	void joinServer(const std::string* pHostname, unsigned short usPort);
	void joinChannel(const std::string* pHostname, const std::string* pChannel) const;
	void isConnectedToServer(const std::string* pHostname) const;
	void isConnectedToCannel(const std::string* pHostname, const std::string* pChannel) const;
	void leaveServer(const std::string* pHostname);
	void leaveChannel(const std::string* pHostname, const std::string* pChannel) const;
	int getServerCount() const;

protected:
	Controller();
	virtual ~Controller();

	static Controller* mObject;

	std::vector<Server*> mServer;
	std::string mNickname;

};

} /* namespace ircbot */
#endif /* CONTROLLER_H_ */
