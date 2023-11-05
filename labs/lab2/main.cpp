#include <logger.h>
#include <glad/glad.h>
#include <GLFWApplication.h>

class Lab2Application : public GLFWApplication {
public:
    Lab2Application(std::string name, std::string version) : GLFWApplication(name, version) {
        
    }

    unsigned Run() const override {
        Log::info("Lab2Application", "Running away from life...");
        return 0;
    }
};

int main() {
    // Start application
    auto app = Lab2Application("Lab 2", "v1");
    auto err = app.Init();
    if (err != app.OK) {
        Log::error("Lab2", "Failed to start application. error: ", err);
        return EXIT_FAILURE;
    }
    app.Run();

    

    return EXIT_SUCCESS;
}