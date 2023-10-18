#include <logger.h>
#include <glad/glad.h>
#include <GLFWApplication.h>

class gigaGLFW : public GLFWApplication {
public:
    gigaGLFW(std::string name, std::string version) : GLFWApplication(name, version) {
        
    }

    void Run() override {
        Log::info("gigaGLFW", "Running away from life...");
    }
};

int main() {
    Log::info("Lab2", "test");
    Log::info("Test", 1, 2.53, 'm');
    auto giga = gigaGLFW("Test", "v0");
    giga.Init();
    giga.Run();

    return 0;
}