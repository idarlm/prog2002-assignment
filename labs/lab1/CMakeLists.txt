add_executable(lab1 main.cpp shaders.h)

target_link_libraries(lab1 PRIVATE glfw glad logger)
target_link_libraries(lab1 PRIVATE GLFWApplication GeometricTools)