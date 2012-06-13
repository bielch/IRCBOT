/*
 * Database.cpp
 *
 *  Created on: 13.06.2012
 *      Author: develop
 */

#include "Database.h"
#include <stdio.h>
#define DB_FILE "/etc/ircbot/log.sqlite"

namespace ircbot {

Database::Database() {

	sqlite3_open(DB_FILE, &mHandle);

	if (!existTable()) {
		createTable();
	}
}

Database::~Database() {
	// TODO Auto-generated destructor stub
}

void Database::createTable() {
	sqlite3_exec(mHandle, "CREATE TABLE log (message text);", NULL, NULL, NULL);
	sqlite3_exec(mHandle, "CREATE TABLE lastseen (user text, lastseen integer);", NULL, NULL, NULL);
}

int Database::existTable() {
	int result = 0;
	sqlite3_stmt* vm;

	sqlite3_prepare(mHandle, "SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'log';", -1, &vm, NULL);
	while (sqlite3_step(vm) != SQLITE_DONE) {
		result = 1;
	}
	sqlite3_finalize(vm);
	return result;
}

int Database::existUser(std::string* user) {
	char * query = sqlite3_mprintf("SELECT * FROM lastseen WHERE user = '%s'", user);

	int result = 0;
	sqlite3_stmt* vm;

	sqlite3_prepare(mHandle, query, -1, &vm, NULL);
	while (sqlite3_step(vm) != SQLITE_DONE) {
		result = 1;
	}
	sqlite3_finalize(vm);

	return result;
}

void Database::createUser(std::string* user) {
	char * query = sqlite3_mprintf("INSERT INTO lastseen (user, lastseen) VALUES ('%s', '0')", user);
	sqlite3_exec(mHandle, query, NULL, NULL, NULL);
}

void Database::updateUser(std::string* user) {
	char * query = sqlite3_mprintf("UPDATE lastseen SET lastseen = strftime('%%s', 'now') WHERE user = '%s'", user);
	sqlite3_exec(mHandle, query, NULL, NULL, NULL);
}

void Database::logx(std::string* msg) {
	char * query = sqlite3_mprintf("INSERT INTO log (message) VALUES ('%s')", msg);
	sqlite3_exec(mHandle, query, NULL, NULL, NULL);
}

} /* namespace ircbot */
