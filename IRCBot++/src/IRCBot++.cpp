#include "Controller.h"
#include "Configuration.h"
#include "debug.h"
#include "function.h"

using namespace std;
using namespace ircbot;

int main(int argc, char* argv[]) {

	DEBUG("Arg count: " << argc);

	argc = 9;

	char* argvX[9];

	char mins[] = "-s\0";
	char server[] = "xs4all.nl.quakenet.org\0";
	char minc[] = "-c\0";
	char channel[] = "#test\0";
	char minp[] = "-p\0";
	char port[] = "6665\0";
	char log[] = "-log\0";
	char deamon[] = "-deamon\0";

	argvX[0] = argv[0];
	argvX[1] = mins;
	argvX[2] = server;
	argvX[3] = minc;
	argvX[4] = channel;
	argvX[5] = minp;
	argvX[6] = port;
	argvX[7] = log;
	argvX[8] = deamon;

	std::string configFilePath("./config.cfg");

	Controller& controller = Controller::getInstance();
	Configuration& configuration = Configuration::getInstance();

	configuration.loadParameter(argc, argvX);
	configuration.loadConfigurationFile(&configFilePath);

	/*if (configuration.mDaemonize)
		daemonize();*/

	controller.startup();

	while (controller.getServerCount() > 0) {
		sleep(10);
	}

	return 0;
}

