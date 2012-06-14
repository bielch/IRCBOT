#include "Controller.h"
#include "Configuration.h"
#include "debug.h"
#include "function.h"

using namespace std;
using namespace ircbot;

int main(int argc, char* argv[]) {

	std::string configFilePath("./config.cfg");

	Controller& controller = Controller::getInstance();
	Configuration& configuration = Configuration::getInstance();

	configuration.loadParameter(argc, argv);
	configuration.loadConfigurationFile(&configFilePath);

	/*if (configuration.mDaemonize)
		daemonize();*/

	controller.startup();

	while (controller.getServerCount() > 0) {
		sleep(10);
	}

	return 0;
}

