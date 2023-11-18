add_library(Rendering STATIC ShaderDataTypes.h VertexBuffer.h VertexBuffer.cpp IndexBuffer.h IndexBuffer.cpp BufferLayout.h "VertexArray.cpp" "VertexArray.h")
add_library(Framework::Rendering ALIAS Rendering)

target_link_libraries(Rendering PUBLIC glad)
target_include_directories(GLFWApplication PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")