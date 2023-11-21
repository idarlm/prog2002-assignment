#ifndef GLFWAPPLICATION_H_
#define GLFWAPPLICATION_H_

#include <string>
#include <GLFW/glfw3.h>

class GLFWApplication {
protected:
    std::string name = "";
    std::string version = "";

    int glVersionMajor = 4;
    int glVersionMinor = 3;

    int width = 1280;
    int height = 720;

    GLFWwindow* window;

public:
    //constructor / destructor
    GLFWApplication(std::string name, std::string version);
    ~GLFWApplication();

    virtual unsigned Init();
    virtual unsigned Run() const = 0;

    std::string getName() { return name; }
    std::string getVersion() { return version; }

    int getWidth() { return width; }
    int getHeight() { return height; }
    float getAspectRatio() { return (float)width / float(height); }

    void setTitle(std::string name, std::string version = "v1.0.0")
    {
        this->name = name;
        this->version = version;
    }

    void setSize(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    void setGlVersion(int major, int minor)
    {
        this->glVersionMajor = major;
        this->glVersionMinor = minor;
    }

    GLFWwindow* getWindow() const { return window; }

    // Error codes
    const unsigned OK = 0;
    const unsigned ERROR_GLFW_INIT_FAILED = 1;
    const unsigned ERROR_GLFW_WINDOW_FAILED = 2;
};

#endif