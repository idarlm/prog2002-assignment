# executable
add_executable(lab2 main.cpp lab2application.h lab2application.cpp "shaders.h")

# link libraries
target_link_libraries(lab2 PRIVATE glad glfw Framework::GLFWApplication Framework::Logger Framework::Rendering Framework::GeometricTools)