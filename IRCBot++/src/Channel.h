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

class Channel {
public:
	Channel(Server* pServer, const std::string* pChannel);
	virtual ~Channel();

protected:
	Server* mServer;
	std::string mNickname;
	std::string mChannel;

	irc_callbacks_t mCallbacks;
	irc_session_t * mSession;

	ircbot_context mContext;

	pthread_t mThread;

	int iret1;

};

} /* namespace ircbot */
#endif /* CHANNEL_H_ */
