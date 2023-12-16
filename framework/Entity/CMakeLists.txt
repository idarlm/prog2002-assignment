add_library(Entity STATIC Entity.h Entity.cpp)
add_library(Framework::Entity ALIAS Entity)

target_link_libraries(Entity PUBLIC glfw glm Framework::Logger Framework::Rendering Framework::InputManager)
target_include_directories(Entity PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")