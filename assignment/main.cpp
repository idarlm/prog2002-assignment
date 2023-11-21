#include <logger.h>
#include "src/AssignmentApplication.h"

int main()
{
	// create glfw app
	auto app = AssignmentApplication("v0.0.0");
	app.setGlVersion(4, 5);
	app.setSize(800, 600);
	app.Init();

	// start application loop
	app.Run();

	return EXIT_SUCCESS;
}