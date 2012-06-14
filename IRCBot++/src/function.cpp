/*
 * function.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "function.h"
#include "structs.h"
#include "Server.h"
#include "Controller.h"
#include "Log.h"
#include "debug.h"

#include <sys/stat.h>



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
	return;
}

void event_connect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {
	struct ircbot_context * ctx = (struct ircbot_context *) irc_get_ctx(session);

	DEBUG("event connected")

	ctx->pConnection->mConnected = true;

	for (unsigned int i = 0; i < ctx->pConnection->mChannel.size(); i++)
		irc_cmd_join(session, ctx->pConnection->mChannel[i]->c_str(), 0);
}

void event_quit(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {
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
		ctx->pController->executeCommand(&command, ctx, &user);
	}

}

void event_numeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count) {
	struct ircbot_context * ctx = (struct ircbot_context *) irc_get_ctx(session);

	char buffer[200];
	std::string message;

	if (event > 400) {

		DEBUG(origin)
		printf("ERROR %d: %s: %s %s %s %s\n", event, origin ? origin : "unknown", params[0], count > 1 ? params[1] : "", count > 2 ? params[2] : "", count > 3 ? params[3] : "");
		sprintf(buffer, "ERROR %d: %s: %s %s %s %s\n", event, origin ? origin : "unknown", params[0], count > 1 ? params[1] : "", count > 2 ? params[2] : "", count > 3 ? params[3] : "");
		message = buffer;

		DEBUG(ctx->pConnection->mlastCommandOrigin);
		ctx->pConnection->sendMsg(&message, &ctx->pConnection->mlastCommandOrigin);
	}
}

void *runSession(void *ptr) {
	DEBUG("thread constructed")
	return (void*) irc_run((irc_session_s*) ptr);
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if (item.size() > 0)
			elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	return split(s, delim, elems);
}

std::string intToString(int i) {
	std::stringstream ss;
	std::string s;
	ss << i;
	s = ss.str();

	return s;
}


void daemonize()
{
  pid_t pid, sid;

  if (getppid() == 1) return;

  pid = fork();
  if ( pid < 0 ) exit (1);

  /* Wenn ein Kindprozess erzeugt wurde, kann der
     Eltern Prozess sich beenden
  */

  if (pid > 0) exit (0);

  /* Neues file mode mask */
  umask(0);

  /* Neue SID Umgebung */
  sid = setsid();
  if (sid < 0) exit(1);

  /* Aendern des Arbeitsverzeichnisses */
  if ((chdir("/") < 0)) exit(1);

  /* Aendern der default Filedescriptoren */
  freopen("/dev/null", "r", stdin);
  freopen("/dev/null", "w", stdout);
  freopen("/dev/null", "w", stderr);
}

}
