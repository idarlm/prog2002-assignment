#include <logger.h>
#include <glad/glad.h>
#include "GLFWApplication.h"

GLFWApplication::GLFWApplication(std::string name, std::string version)
    : name(name), version(version) {
    Log::info("GLFWApplication", "Starting application: " + name + " (" + version + ")");
}

/**
 * Destroy window and perform additional cleanup.
*/
GLFWApplication::~GLFWApplication() {
    Log::info("GLFWApplication", "Destroying window...");

    glfwDestroyWindow(window);

    Log::info("GLFWApplication", "Goodbye!");
}

/**
 * Create a window with new OpenGL context.
*/
unsigned GLFWApplication::Init() {
    // Check that we haven't already created the window.
    // Will probably never happen, but better safe than sorry.
    if(window) {
        Log::error("GLFWApplication", "Multiple calls to Init()");
        return ERROR_MULTIPLE_INIT;
    }

    // GLFW initialization
    if(!glfwInit())
    {
        Log::error("GLFWApplication", "Failed to initialize GLFW.");
        return ERROR_GLFW_INIT_FAILED;
    }

    // set GLFW error callback
    glfwSetErrorCallback( 
        [](int code, const char* msg)
        {
            Log::error("GLFW Callback", "Code = ", code, ", Message = \"", msg, '"');
        }
    );

    Log::info("GLFWApplication", "GLFW Initialized.");

    // window creation
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(480, 360, "Test window", NULL, NULL);

    if(!window)
    {
        Log::error("GLFWApplication", "Failed to create glfw window");
        return ERROR_GLFW_WINDOW_FAILED;
    }
    Log::info("GLFWApplication", "Created Window");

    glfwMakeContextCurrent(window);

    // OpenGL initialization
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // OpenGL debugging settings
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(
        [] (GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam)
        {            
            Log::error(
                "OpenGL Callback", 
                ", type = ", type,
                ", severity = ", severity,
                ", message = \"", message, '"'
                );
        },
        0
    );
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    return OK;
}
