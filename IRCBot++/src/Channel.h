/*
 * Channel.h
 *
 *  Created on: 13.06.2012
 *      Author: develop
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <stdlib.h>
#include <libircclient.h>
#include <pthread.h>

namespace ircbot {

class Channel {
public:
	Channel();
	virtual ~Channel();

protected:
	irc_callbacks_t mCallbacks;
	irc_session_t * mSession;
	pthread_t mThread;
	int  iret1;
};

} /* namespace ircbot */
#endif /* CHANNEL_H_ */
