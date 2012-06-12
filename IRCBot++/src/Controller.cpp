/*
 * Controller.cpp
 *
 *  Created on: 12.06.2012
 *      Author: develop
 */

#include "Controller.h"

namespace ircbot {

Controller* Controller::mObject = 0;

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

Controller& Controller::getInstance(){
	if(!mObject)
		mObject = new Controller();

	return *mObject;
}

int Controller::getServerCount() const{
	return mServer.size();
}
} /* namespace ircbot */
