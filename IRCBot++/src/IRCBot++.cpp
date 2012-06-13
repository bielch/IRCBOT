#include "Controller.h"
#include "Configuration.h"
#include "debug.h"

using namespace std;
using namespace ircbot;

int main(int argc, char* argv[]) {

	DEBUG("Arg count: " << argc);

	argc = 9;

	char path[] = "asdashdasd\0";
	char mins[] = "-s\0";
	char server[] = "xs4all.nl.quakenet.org\0";
	char minc[] = "-c\0";
	char channel[] = "#test\0";
	char minp[] = "-p\0";
	char port[] = "6665\0";
	char log[] = "-log\0";
	char deamon[] = "-deamon\0";

	argv[0] = path;
	argv[1] = mins;
	argv[2] = server;
	argv[3] = minc;
	argv[4] = channel;
	argv[5] = minp;
	argv[6] = port;
	argv[7] = log;
	argv[8] = deamon;

	std::string configFilePath("./config.cfg");

	Controller& controller = Controller::getInstance();
	Configuration& configuration = Configuration::getInstance();

	configuration.loadParameter(argc, argv);
	configuration.loadConfigurationFile(&configFilePath);

	controller.startup();

	while (controller.getServerCount() > 0) {
		sleep(10);
	}

	return 0;
}

