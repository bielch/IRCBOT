/*
 * Server.h
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "Channel.h"
#include <vector>

namespace ircbot {

class Server {
	friend class Channel;
public:
	Server(const std::string* pHostname, unsigned short usPort, std::string* pNickname);
	virtual ~Server();
protected:
	std::string* mNickname;
	std::string mHostname;

	unsigned short mPort;

	std::vector<Channel> mChannel;
};

} /* namespace ircbot */
#endif /* SERVER_H_ */
