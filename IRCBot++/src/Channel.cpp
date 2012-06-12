/*
 * Channel.cpp
 *
 *  Created on: 13.06.2012
 *      Author: develop
 */

#include "Channel.h"
#include <string.h>

namespace ircbot {

Channel::Channel() {
	// Initialize the callbacks
	memset(&mCallbacks, 0, sizeof(mCallbacks));

	// Set up the callbacks we will use
	mCallbacks.event_connect = event_connect;
	mCallbacks.event_join = event_join;
	mCallbacks.event_numeric = event_numeric;
	mCallbacks.event_quit = event_quit;
	//callbacks.event_channel_notice = event_channel_notice;
	//callbacks.event_notice = event_channel_notice;
	mCallbacks.event_channel = event_channel_notice;
	mCallbacks.event_privmsg = event_channel_notice;

	// And create the IRC session; 0 means error
	mSession = irc_create_session(&mCallbacks);

	iret1 = pthread_create(&mThread, NULL, runSession, (void*) mSession);
}

Channel::~Channel() {
	pthread_join(mThread, NULL);
}

} /* namespace ircbot */
