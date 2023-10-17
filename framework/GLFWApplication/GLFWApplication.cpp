#include "GLFWApplication.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <logger.h>

void GLFWApplication::Init() {
    // GLFW initialization
    if(!glfwInit())
    {
        Log::error("GLFWApplication", "Failed to initialize GLFW.");
    }

    Log::info("GLFWApplication", "GLFW Initialized.");

    // window creation
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    auto window = glfwCreateWindow(480, 360, "Test window", NULL, NULL);

    if(!window)
    {
        Log::error("GLFWApplication", "Failed to create glfw window");
    }
    Log::info("GLFWApplication", "Created Window");

    glfwMakeContextCurrent(window);

    // OpenGL initialization
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // set debug callbacks

}