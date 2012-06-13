/*
 * Database.h
 *
 *  Created on: 13.06.2012
 *      Author: develop
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <sqlite3.h>
#include <string>

namespace ircbot {

class Database {
public:
	Database();
	virtual ~Database();

	void createTable();
	int existTable();
	int existUser(std::string* user);
	int getUser(std::string* user);
	void createUser(std::string* user);
	void updateUser(std::string* user);
	void logx(std::string* msg);

protected:
	sqlite3* mHandle;
};

} /* namespace ircbot */
#endif /* DATABASE_H_ */
