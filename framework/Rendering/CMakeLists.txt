add_library(Rendering STATIC ShaderDataTypes.h VertexBuffer.h VertexBuffer.cpp IndexBuffer.h IndexBuffer.cpp BufferLayout.h "VertexArray.cpp" "VertexArray.h" "Shader.h" "Shader.cpp" "RenderCommands.h" "Camera.h" "OrthographicCamera.h" "OrthographicCamera.cpp" "PerspectiveCamera.h" "PerspectiveCamera.cpp" "TextureManager.h" "TextureManager.cpp")
add_library(Framework::Rendering ALIAS Rendering)

target_link_libraries(Rendering PUBLIC glad glm stb Framework::Logger)
target_include_directories(GLFWApplication PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_definitions(
	Rendering PRIVATE
	STB_IMAGE_IMPLEMENTATION
	STB_IMAGE_STATIC
)