# subdirectory containing application specific code
add_subdirectory(src)

# executable
add_executable(assignment main.cpp)

# link libraries
target_link_libraries(assignment PRIVATE AssignmentSrc Framework::InputManager)

# custom commands for copying images
add_custom_command(
	TARGET assignment POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/cube_texture.png
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/cube_texture.png
)

add_custom_command(
	TARGET assignment POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/floor_texture.png
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/floor_texture.png
)

target_compile_definitions(
	assignment PRIVATE
	TEXTURES_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/"
)
