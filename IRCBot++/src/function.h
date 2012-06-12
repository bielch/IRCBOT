/*
 * function.h
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <stdio.h>

namespace ircbot {

int fileExists(const char* filepath);

int fileCreate(const char* filepath);

void fileLog(FILE* logfile, const char* msg);

} /* namespace ircbot */
#endif /* FUNCTION_H_ */
