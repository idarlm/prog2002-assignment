#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <logger.h>
#include "lab3application.h"

Lab3Application* app;

void handleInput(GLFWwindow* window, int key, int scancode, int action, int mod)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_LEFT:     app->selectionX--; break;
        case GLFW_KEY_RIGHT:    app->selectionX++; break;
        case GLFW_KEY_DOWN:     app->selectionY--; break;
        case GLFW_KEY_UP:       app->selectionY++; break;
        case GLFW_KEY_ESCAPE:   glfwSetWindowShouldClose(app->getWindow(), GLFW_TRUE); break;
        }
    }
}

int main() 
{
    // Start application
    app = new Lab3Application("Lab 3", "v3");
    auto err = app->Init();
    if (err != app->OK) {
        Log::error("Lab3", "Failed to start application. error: ", err);
        return EXIT_FAILURE;
    }

    glfwSetKeyCallback(app->getWindow(), handleInput);
    app->Run();
    delete app;

    return EXIT_SUCCESS;
}