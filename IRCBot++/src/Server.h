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

class Server {
	friend class Controller;
public:
	Server(std::string* pHostname, unsigned short usPort, std::string* pNickname);
	virtual ~Server();

	void changeNickname(std::string* pNickname);
	void sendMsg(std::string* pMessage, std::string* pTarget);
	void joinChannel(std::string* pChannel);
	void leaveChannel(std::string* pChannel);
	void leaveServer();

	std::string mHostname;
	std::string mNickname;
	std::string mlastCommandOrigin;
	std::vector<std::string*> mChannel;

	irc_callbacks_t mCallbacks;
	irc_session_t * mSession;

	ircbot_context mContext;

	pthread_t mThread;

	int iret1;
	unsigned short mPort;

	bool mConnected;

};

} /* namespace ircbot */
#endif /* CHANNEL_H_ */
