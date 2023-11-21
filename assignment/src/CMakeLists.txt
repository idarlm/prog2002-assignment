add_library(AssignmentSrc STATIC "AssignmentApplication.h" "AssignmentApplication.cpp" "Entity.h" "Entity.cpp" "Input.h" "Input.cpp" "Prefabs.h" "AssignmentShaders.h")

target_link_libraries(
	AssignmentSrc PUBLIC 
	glad glfw stb 
	Framework::GLFWApplication 
	Framework::Logger 
	Framework::Rendering 
	Framework::GeometricTools
)
