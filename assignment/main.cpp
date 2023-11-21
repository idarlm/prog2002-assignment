#include <logger.h>
#include "src/AssignmentApplication.h"
#include "src/Input.h"

Input* input;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (auto& b : input->bindings)
	{
		if (b.second.keyCode != key)
		{
			continue;
		}

		// set held
		b.second.held |= action == GLFW_PRESS;
		b.second.held &= action != GLFW_RELEASE;

		// set pressed
		b.second.pressed = action == GLFW_PRESS;

		// set released
		b.second.released = action == GLFW_RELEASE;
	}
}

int main()
{
	// set up input manager
	input = Input::GetInstance();
	Input::BindButton("Quit", GLFW_KEY_Q);

	// create glfw app
	auto app = AssignmentApplication("v0.0.0");
	app.setGlVersion(4, 5);
	app.setSize(800, 600);
	app.Init();
	glfwSetKeyCallback(app.getWindow(), keyCallback);

	// start application loop
	app.Run();

	return EXIT_SUCCESS;
}