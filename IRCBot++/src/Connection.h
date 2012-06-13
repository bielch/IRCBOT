/*
 * Channel.h
 *
 *  Created on: 13.06.2012
 *      Author: develop
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <stdlib.h>
#include <string>
#include <libircclient.h>
#include <pthread.h>
#include "structs.h"

namespace ircbot {

class Server;

class Connection {
	friend class Controller;
public:
	Connection(std::string* pHostname, unsigned short usPort, std::string* pNickname, std::string* pChannel = 0);
	virtual ~Connection();

	void changeNickname(std::string* pNickname);

	std::string mHostname;
	std::string mNickname;
	std::string mChannel;

	irc_callbacks_t mCallbacks;
	irc_session_t * mSession;

	ircbot_context mContext;

	pthread_t mThread;

	int iret1;
	unsigned short mPort;

};

} /* namespace ircbot */
#endif /* CHANNEL_H_ */
