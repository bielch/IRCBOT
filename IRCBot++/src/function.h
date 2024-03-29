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
#include <sstream>
#include <vector>
#include <libircclient.h>

namespace ircbot {

int fileExists(const char* filepath);

int fileCreate(const char* filepath);

void fileLog(FILE* logfile, const char* msg);

void removeWhitespaces(std::string& pString);

void removeFrontWhitespaces(std::string& pString);

void event_join(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

void event_connect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

void event_quit(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

void event_channel_notice(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

void event_numeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count);

void *runSession(void *ptr);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

std::string intToString(int i);

void daemonize();

} /* namespace ircbot */
#endif /* FUNCTION_H_ */
