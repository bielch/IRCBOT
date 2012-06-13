/*
 * structs.h
 *
 *  Created on: 13.06.2012
 *      Author: develop
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <string>
#include <vector>

namespace ircbot {

class Server;
class Channel;
class Database;
class Controller;

struct ircbot_context {
	Channel* pChannel;
	Server* pServer;
	Database* pDatabase;
	Controller* pController;
};

struct server_context{
	std::string dHostname;
	std::string dNickname;
	std::vector<std::string*> dChannel;
	unsigned short dPort;
};

}

#endif /* STRUCTS_H_ */
