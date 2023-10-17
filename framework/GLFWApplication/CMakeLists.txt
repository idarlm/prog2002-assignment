add_library(GLFWApplication STATIC GLFWApplication.h GLFWApplication.cpp)

target_link_libraries(GLFWApplication PRIVATE glfw glad logger)

target_include_directories(GLFWApplication PRIVATE "${PROJECT_SOURCE_DIR}/framework/Logger")