#include <RenderCommands.h>
#include "AssignmentApplication.h"

using namespace RenderCommands;

AssignmentApplication::AssignmentApplication(std::string version)
	: GLFWApplication("Assignment", version) {}

// Load all necessary data
unsigned AssignmentApplication::Init()
{
	GLFWApplication::Init();

	return OK;
}

// Start application loop
unsigned AssignmentApplication::Run() const
{
	// Use depth testing by default
	EnableDepthTest();
	SetClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		Clear();

		glfwSwapBuffers(window);
	}

	return OK;
}