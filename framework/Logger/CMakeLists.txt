add_library(logger STATIC logger.h logger.cpp)
add_library(Framework::Logger ALIAS logger)

target_include_directories(GLFWApplication PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")