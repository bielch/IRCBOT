/*
 * Server.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "Server.h"

namespace ircbot {

Server::Server(const std::string* pHostname, unsigned short usPort, std::string* pNickname) :
		mNickname(pNickname), mHostname(*pHostname), mPort(usPort) {
	// TODO Auto-generated constructor stub

}

Server::~Server() {
	// TODO Auto-generated destructor stub
}

} /* namespace ircbot */
