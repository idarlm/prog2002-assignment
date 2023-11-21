#include <logger.h>
#include <TextureManager.h>
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
		b.second.held = (bool)action;

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
	Input::BindButton("Left", GLFW_KEY_LEFT);
	Input::BindButton("Right", GLFW_KEY_RIGHT);
	Input::BindButton("Up", GLFW_KEY_UP);
	Input::BindButton("Down", GLFW_KEY_DOWN);
	Input::BindButton("Select", GLFW_KEY_ENTER);
	Input::BindButton("RotateLeft", GLFW_KEY_L);
	Input::BindButton("RotateRight", GLFW_KEY_H);
	Input::BindButton("ZoomIn", GLFW_KEY_P);
	Input::BindButton("ZoomOut", GLFW_KEY_O);
	Input::BindButton("ToggleTextures", GLFW_KEY_T);

	// create glfw app
	auto app = AssignmentApplication("v0.0.0");
	app.setGlVersion(4, 5);
	app.setSize(800, 600);
	app.Init();
	glfwSetKeyCallback(app.getWindow(), keyCallback);

	// load textures
	auto texMan = TextureManager::GetInstance();
	texMan->LoadTexture2DRGBA(std::string("floor_texture.png"), TEXTURES_DIR, 0);
	texMan->LoadCubeMapRGBA(std::string("cube_texture.png"), TEXTURES_DIR, 1);

	// start application loop
	app.Run();

	return EXIT_SUCCESS;
}