add_library(Rendering STATIC ShaderDataTypes.h VertexBuffer.h VertexBuffer.cpp)
add_library(Framework::Rendering ALIAS Rendering)

target_link_libraries(Rendering PUBLIC glad)
target_include_directories(GLFWApplication PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")