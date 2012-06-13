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

class Connection;
class Database;
class Controller;

struct ircbot_context {
	Connection* pConnection;
	Database* pDatabase;
	Controller* pController;
};

struct connection_context{
	std::string dHostname;
	std::string dNickname;
	std::string dChannel;
	unsigned short dPort;
};

}

#endif /* STRUCTS_H_ */
