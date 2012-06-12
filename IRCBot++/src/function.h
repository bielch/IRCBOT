/*
 * function.h
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <stdio.h>
#include <string>
#include <libircclient.h>

namespace ircbot {

int fileExists(const char* filepath);

int fileCreate(const char* filepath);

void fileLog(FILE* logfile, const char* msg);

void removeWhitespaces(std::string& pString);

void event_join(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

void event_connect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

void event_quit(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

void event_channel_notice(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

void event_numeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count);

void *runSession(void *ptr);

} /* namespace ircbot */
#endif /* FUNCTION_H_ */
