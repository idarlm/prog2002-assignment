# executable
add_executable(lab3 main.cpp lab3application.h lab3application.cpp "shaders.h")

# link libraries
target_link_libraries(lab3 PRIVATE glad glfw stb Framework::GLFWApplication Framework::Logger Framework::Rendering Framework::GeometricTools)

# custom commands for copying images
add_custom_command(
	TARGET lab3 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/cube_texture.png
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/cube_texture.png
)

add_custom_command(
	TARGET lab3 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/floor_texture.png
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/floor_texture.png
)

target_compile_definitions(
	lab3 PRIVATE
	TEXTURES_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/"
)
