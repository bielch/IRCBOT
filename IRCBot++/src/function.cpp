/*
 * function.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "function.h"
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

void removeWhitespaces(std::string& pString){
	for(unsigned int i = 0; i < pString.size(); i++)
		if(pString[i] == ' ')
			pString.erase(i, 1);
}

}
