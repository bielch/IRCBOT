/*
 * structs.h
 *
 *  Created on: 13.06.2012
 *      Author: develop
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

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

}

#endif /* STRUCTS_H_ */
