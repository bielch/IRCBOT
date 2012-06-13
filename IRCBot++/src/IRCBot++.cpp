#include "Controller.h"
#include "Configuration.h"

using namespace std;
using namespace ircbot;

int main(int argc, char* argv[]) {

	std::string configFilePath("./config.cfg");

	Controller& controller = Controller::getInstance();
	Configuration& configuration = Configuration::getInstance();

	configuration.loadParameter(argc, argv);
	configuration.loadConfigurationFile(&configFilePath);

	controller.startup();

	while (controller.getServerCount() > 0)
		sleep(1000);


	return 0;
}


