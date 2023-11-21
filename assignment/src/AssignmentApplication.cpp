#include <logger.h>
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
	auto cubeShader = std::make_shared<Shader>(Shaders::cubeVertShader, Shaders::cubeFragShader);

	// create vertex arrays
	auto boardArray = Prefabs::MakeBoard();
	auto cubeArray = Prefabs::MakeCube();

	// create 32 cubes
	for (int i = 0; i < 32; i++)
	{
		auto cube = Entity::MakeEntity(cubeArray, cubeShader);
		cube->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
		cube->SetPosition(glm::vec3((float)i / 8.f, 0.f, 0.f));
		AddEntity(cube);
	}

	auto board = Entity::MakeEntity(boardArray, boardShader);
	board->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	board->SetRotation(glm::radians(-90.f), glm::vec3(1.0, 0.0f, 0.0f));
	AddEntity(board);

	Log::info("App", "Spawned ", entities.size(), " entities");

	return OK;
}

// Start application loop
unsigned AssignmentApplication::Run() const
{
	// Use depth testing
	EnableDepthTest();
	SetClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	// set up camera
	auto camera = PerspectiveCamera();
	camera.SetPosition(glm::vec3(0.0f, 1.0f, 1.0f));
	camera.SetAspectRatio(800.f / 600.f);

	// set up tile selector
	unsigned x = 0, y = 0;

	// logical representation of board
	int board[8 * 8] = {-1};
	for (int i = 0; i < 64; i++)
	{
		if (i < 16)
			board[i] = i;
		else if (i > 47)
			board[i] = i - 32;
		else
			board[i] = -1;
	}
	
	float time = 0.f;
	while (!glfwWindowShouldClose(window))
	{
		glfwSetWindowShouldClose(window, Input::ButtonDown("Quit"));

		// Update input flags and clear screen
		Input::ClearFlags();
		glfwPollEvents();
		Clear();

		float dt = glfwGetTime() - time;
		time = glfwGetTime();

		// update tile selector
		Input::ButtonDown("Right")	&& x < 7 && ++x;
		Input::ButtonDown("Left")	&& x > 0 && --x;
		Input::ButtonDown("Up")		&& y < 7 && ++y;
		Input::ButtonDown("Down")	&& y > 0 && --y;

		// update all entities
		for (auto& e : entities)
		{
			auto id = e->GetID();

			// Update cubes
			if (id != 32)
			{
				auto team = id / 16;
				int pos = -1;
				for (int i = 0; i < 64; i++)
				{
					if (board[i] == id)
						pos = i;
				}

				float posx = pos % 8;
				float posz = float(pos / 8);
				posx = (posx / 8.f) - 0.5f + 0.5f / 8.f;
				posz = (-posz / 8.f) + 0.5f - 0.5f / 8.f;

				e->SetPosition(glm::vec3(posx, 0.075f, posz));

				// update uniforms
				auto s = e->GetShader();
				s->Bind();
				s->UploadUniformMat4x4("viewProjection", camera.GetViewProjectionMatrix());
				s->UploadUniformMat4x4("model", e->GetMatrix());

				auto loc = s->GetUniformLocation("alt_color");
				glUniform1i(loc, team);

				// draw
				if(pos != -1)
					e->Update(dt);
			}

			// Update board
			if (id == 32)
			{
				// update uniforms
				auto s = e->GetShader();
				s->Bind();
				s->UploadUniformMat4x4("viewProjection", camera.GetViewProjectionMatrix());
				s->UploadUniformMat4x4("model", e->GetMatrix());
				auto loc = s->GetUniformLocation("selected_vertex");
				glUniform1i(loc, x + (9 * y));

				// draw
				e->Update(dt);
			}
		}

		glfwSwapBuffers(window);
	}

	return OK;
}