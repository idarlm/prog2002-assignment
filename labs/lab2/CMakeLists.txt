# executable
add_executable(lab2 main.cpp lab2application.cpp lab2application.h)

# link libraries
target_link_libraries(lab2 PRIVATE glfw glad Framework::GLFWApplication Framework::Logger)