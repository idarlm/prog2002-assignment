add_executable(lab1 main.cpp)

add_library(logger STATIC logger.h logger.cpp)

target_link_libraries(lab1 PRIVATE glfw glad logger)