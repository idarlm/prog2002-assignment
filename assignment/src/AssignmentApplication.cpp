#include <RenderCommands.h>
#include <PerspectiveCamera.h>
#include "AssignmentApplication.h"
#include "Input.h"
#include "Prefabs.h"
#include "AssignmentShaders.h"

using namespace RenderCommands;

AssignmentApplication::AssignmentApplication(std::string version)
	: GLFWApplication("Assignment", version) {}

// Load all necessary data
unsigned AssignmentApplication::Init()
{
	GLFWApplication::Init();

	// compile shaders
	auto boardShader = std::make_shared<Shader>(Shaders::boardVertShader, Shaders::boardFragShader);

	// create vertex arrays
	auto boardArray = Prefabs::MakeBoard();

	auto board = Entity::MakeEntity(boardArray, boardShader);
	board->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	board->SetRotation(-90.f, glm::vec3(1.0, 0.0f, 0.0f));
	AddEntity(board);

	return OK;
}

// Start application loop
unsigned AssignmentApplication::Run() const
{
	// Use depth testing
	EnableDepthTest();
	SetClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	auto camera = PerspectiveCamera();
	camera.SetPosition(glm::vec3(0.0f, 1.0f, 0.5f));
	camera.SetAspectRatio(800.f / 600.f);
	float time = 0.f;

	while (!glfwWindowShouldClose(window))
	{
		glfwSetWindowShouldClose(window, Input::ButtonDown("Quit"));
		glfwPollEvents();
		Clear();

		float dt = glfwGetTime() - time;
		time = glfwGetTime();

		// update all entities
		for (auto& e : entities)
		{
			auto s = e->GetShader();
			s->UploadUniformMat4x4("viewProjection", camera.GetViewProjectionMatrix());
			s->UploadUniformMat4x4("model", e->GetMatrix());
			auto loc = s->GetUniformLocation("selected_vertex");
			glUniform1i(loc, 1);
			e->Update(dt);
		}

		glfwSwapBuffers(window);
	}

	return OK;
}