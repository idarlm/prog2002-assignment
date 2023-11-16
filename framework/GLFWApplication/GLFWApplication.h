#ifndef GLFWAPPLICATION_H_
#define GLFWAPPLICATION_H_

#include <iostream>
#include <GLFW/glfw3.h>

class GLFWApplication {
protected:
    std::string name = "";
    std::string version = "";

    GLFWwindow* window;
public:
    //constructor / destructor
    GLFWApplication(std::string name, std::string version);
    ~GLFWApplication();

    virtual unsigned Init();
    virtual unsigned Run() const = 0;

    inline std::string getName() { return name; }
    inline std::string getVersion() { return version; }

    // Error codes
    const unsigned OK = 0;
    const unsigned ERROR_GLFW_INIT_FAILED = 1;
    const unsigned ERROR_GLFW_WINDOW_FAILED = 2;
};

#endif