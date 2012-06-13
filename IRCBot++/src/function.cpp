/*
 * function.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "function.h"
#include "structs.h"
#include "Connection.h"
#include "Controller.h"
#include "Log.h"
#include "debug.h"

namespace ircbot {

int fileExists(const char* filepath) {
	int result = 0;
	FILE* file = fopen(filepath, "r");

	if (file)
		result = 1;

	fclose(file);

	return result;
}

int fileCreate(const char* filepath) {
	int result = 0;
	FILE* file = fopen(filepath, "w");

	if (file)
		result = 1;

	fclose(file);

	return result;

}

void fileLog(FILE* logfile, const char* msg) {
	if (logfile && msg) {
		fputs(msg, logfile);
		fputs("\n", logfile);
		fflush(logfile);
	}
}

void removeWhitespaces(std::string& pString) {
	for (unsigned int i = 0; i < pString.size(); i++)
		if (pString[i] == ' ')
			pString.erase(i, 1);
}

void removeFrontWhitespaces(std::string& pString) {
	for (unsigned int i = 0; i < pString.size(); i++)
		if (pString[i] == ' ')
			pString.erase(i, 1);
		else
			return;
}

void event_join(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {

	if (!origin)
		return;

	DEBUG("join event");
}

void event_connect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {
	struct ircbot_context * ctx = (struct ircbot_context *) irc_get_ctx(session);
	irc_cmd_join(session, ctx->pConnection->mChannel.c_str(), 0);
}

void event_quit(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {

	if (!origin)
		return;
}

void event_channel_notice(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {

	if (!origin || count != 2)
		return;

	struct ircbot_context * ctx = (struct ircbot_context *) irc_get_ctx(session);
	std::string message = params[1];
	std::string user = origin;
	std::string command;

	printf("%s\n", message.c_str());

	ctx->pLog->logMessage(&message);

	if (!ctx->pLog->mDatabase->existUser(&user))
		ctx->pLog->mDatabase->createUser(&user);

	ctx->pLog->mDatabase->updateUser(&user);

	DEBUG("Message:" << message);
	DEBUG("User:" << user);

	if (message.compare(0, ctx->pConnection->mNickname.size(), ctx->pConnection->mNickname) == 0) {
		command = message.substr(ctx->pConnection->mNickname.size(), message.size() - ctx->pConnection->mNickname.size());
		DEBUG("Command:" << command);
		ctx->pController->executeCommand(&command, ctx);
	}

}

void event_numeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count) {
	if (event > 400) {
		struct ircbot_context * ctx = (struct ircbot_context *) irc_get_ctx(session);
		ctx->pController->removeConnection(ctx->pConnection);
		printf("ERROR %d: %s: %s %s %s %s\n", event, origin ? origin : "unknown", params[0], count > 1 ? params[1] : "", count > 2 ? params[2] : "", count > 3 ? params[3] : "");
	}
}

void *runSession(void *ptr) {
	return (void*) irc_run((irc_session_s*) ptr);
}

}
