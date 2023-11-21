add_library(AssignmentSrc STATIC "AssignmentApplication.h" "AssignmentApplication.cpp" "Entity.h")

target_link_libraries(
	AssignmentSrc PUBLIC 
	glad glfw stb 
	Framework::GLFWApplication 
	Framework::Logger 
	Framework::Rendering 
	Framework::GeometricTools
)
