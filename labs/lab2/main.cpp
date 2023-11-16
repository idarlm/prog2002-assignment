#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <logger.h>
#include "lab2application.h"


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