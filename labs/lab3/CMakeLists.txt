# executable
add_executable(lab3 main.cpp lab3application.h lab3application.cpp "shaders.h")

# link libraries
target_link_libraries(lab3 PRIVATE glad glfw Framework::GLFWApplication Framework::Logger Framework::Rendering Framework::GeometricTools)