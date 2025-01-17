#include <logger.h>
#include <glad/glad.h>
#include "GLFWApplication.h"

GLFWApplication::GLFWApplication(std::string name, std::string version)
    : name(name), version(version), window(nullptr) {
    Log::info("GLFWApplication", "Starting application: " + name + " (" + version + ")");
}

/**
 * Destroy window and perform additional cleanup.
*/
GLFWApplication::~GLFWApplication() {
    glfwDestroyWindow(window);

    Log::info("GLFWApplication", "Goodbye!");
}

/**
 * Create a window with new OpenGL context.
*/
unsigned GLFWApplication::Init() {
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

    // window creation
    Log::info("GLFWApplication", "OpenGL version: ", glVersionMajor, ".", glVersionMinor);
    Log::info("GLFWApplication", "Window size: ", width, "x", height);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersionMinor);
    window = glfwCreateWindow(width, height, (name + " (" + version + ")").c_str(), NULL, NULL);

    if(!window)
    {
        Log::error("GLFWApplication", "Failed to create glfw window");
        return ERROR_GLFW_WINDOW_FAILED;
    }

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
                "type = ", type,
                ", severity = ", severity,
                "\n", message
                );
        },
        0
    );
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    // OpenGL debug info
    Log::info("OpenGL", "Vendor: ", glGetString(GL_VENDOR));
    Log::info("OpenGL", "Renderer: ", glGetString(GL_RENDERER));
    Log::info("OpenGL", "OpenGL version: ", glGetString(GL_VERSION));

    return OK;
}
