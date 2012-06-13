/*
 * Channel.cpp
 *
 *  Created on: 13.06.2012
 *      Author: develop
 */

#include "Connection.h"
#include "Controller.h"
#include "Log.h"
#include "function.h"
#include "debug.h"
#include <string.h>

namespace ircbot {

Connection::Connection(std::string* pHostname, unsigned short usPort, std::string* pNickname, std::string* pChannel) :
		mHostname(*pHostname), mNickname(*pNickname), mPort(usPort) {

	DEBUG("connection constructor");

	if(pChannel)
		mChannel = *pChannel;

	mContext.pLog = &Log::getInstance();
	mContext.pController = &Controller::getInstance();
	mContext.pConnection = this;

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

	if(!mSession){
		DEBUG("Session konnte nicht erzeugt werden.");
	}

	irc_set_ctx(mSession, &mContext);
	irc_option_set(mSession, LIBIRC_OPTION_STRIPNICKS);

	// Initiate the IRC server connection
	if (irc_connect(mSession, mHostname.c_str(), mPort, 0, mNickname.c_str(), 0, 0)) {
		printf("Could not connect: %s\n", irc_strerror(irc_errno(mSession)));
	} else {
		iret1 = pthread_create(&mThread, NULL, runSession, (void*) mSession);
	}

	DEBUG("Connstruct succesfull");
}

Connection::~Connection() {
	pthread_join(mThread, NULL);
}

void Connection::changeNickname(std::string* pNickname){
	mNickname = *pNickname;
	irc_cmd_nick(mSession, mNickname.c_str());
}

} /* namespace ircbot */
