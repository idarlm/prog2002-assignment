add_library(InputManager STATIC Input.h Input.cpp)
add_library(Framework::InputManager ALIAS InputManager)

target_link_libraries(InputManager PRIVATE Framework::Logger glfw)
target_include_directories(InputManager PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")