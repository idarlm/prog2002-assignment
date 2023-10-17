#include <iostream>

class GLFWApplication {
public:
    //constructor / destructor
    GLFWApplication(std::string name, std::string version);
    ~GLFWApplication();

    virtual void Init();
    virtual void Run() const = 0;
};