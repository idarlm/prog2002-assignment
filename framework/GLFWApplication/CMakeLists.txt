add_library(GLFWApplication STATIC GLFWApplication.h GLFWApplication.cpp)
add_library(Framework::GLFWApplication ALIAS GLFWApplication)

target_link_libraries(GLFWApplication PUBLIC glfw glad logger)
target_include_directories(GLFWApplication PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")