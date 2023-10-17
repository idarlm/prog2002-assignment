add_executable(lab1 main.cpp)

target_link_libraries(lab1 PRIVATE glfw glad logger)

target_include_directories(lab1 PRIVATE "${PROJECT_SOURCE_DIR}/framework")