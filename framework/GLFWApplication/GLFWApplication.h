#include <iostream>

class GLFWApplication {
private:
    std::string name = "";
    std::string version = "";

public:
    //constructor / destructor
    GLFWApplication(std::string name, std::string version);
    ~GLFWApplication();

    virtual void Init();
    virtual void Run() = 0;

    inline std::string getName() { return name; }
    inline std::string getVersion() { return version; }
};