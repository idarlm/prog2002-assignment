# executable
add_executable(lab2 main.cpp)

# link libraries
target_link_libraries(lab2 PRIVATE glfw glad GLFWApplication logger)

target_include_directories(lab2 PRIVATE "${PROJECT_SOURCE_DIR}/framework")