/*
 * function.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "function.h"
#include <libircclient.h>
#include <vector>

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

void event_join(irc_session_t * session, const char * event,
		const char * origin, const char ** params, unsigned int count) {

	if (!origin)
		return;
}

void event_connect(irc_session_t * session, const char * event,
		const char * origin, const char ** params, unsigned int count) {
	/*struct ircbot_context * ctx = (struct ircbot_context *) irc_get_ctx(session);
	 struct ircbot_channel* temp = ctx->channel;

	 while (temp != NULL) {
	 irc_cmd_join(session, temp->name, 0);
	 temp = temp->nextchannel;
	 }*/
}

void event_quit(irc_session_t * session, const char * event,
		const char * origin, const char ** params, unsigned int count) {

	if (!origin)
		return;
}

void event_channel_notice(irc_session_t * session, const char * event,
		const char * origin, const char ** params, unsigned int count) {

	if (!origin || count != 2)
		return;

	/*struct ircbot_context * ctx = (struct ircbot_context *) irc_get_ctx(session);

	 printf("%s\n", params[1]);

	 if(!existUser(ctx->dbhandle, origin)){
	 createUser(ctx->dbhandle, origin);
	 }
	 updateUser(ctx->dbhandle, origin);

	 if(ctx->log){
	 fileLog(ctx->logfile, params[1]);
	 logx(ctx->dbhandle, params[1]);
	 }
	 /char* temp = malloc(sizeof(char)* strlen(params[1]));
	 memset(temp, 0, strlen(params[1]));
	 memcpy(temp, params[1], strlen(params[1]));*
	 processCommand(session, ctx, params[1]);*/

}

void event_numeric(irc_session_t * session, unsigned int event,
		const char * origin, const char ** params, unsigned int count) {
	if (event > 400) {
		printf("ERROR %d: %s: %s %s %s %s\n", event,
				origin ? origin : "unknown", params[0],
				count > 1 ? params[1] : "", count > 2 ? params[2] : "",
				count > 3 ? params[3] : "");
	}
}

void *runSession(void *ptr) {
	irc_run((irc_session_s*) ptr);
}

}
