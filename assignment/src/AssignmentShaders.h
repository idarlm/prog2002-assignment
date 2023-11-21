#ifndef ASSIGNMENTSHADERS_H_
#define ASSIGNMENTSHADERS_H_

#include <string>

namespace Shaders
{
    const std::string boardVertShader = R"(
        #version 430 core

        layout(location = 0) in vec2 position;
        layout(location = 1) in vec2 tex_coords;

        uniform int selected_vertex;
        uniform mat4 viewProjection;
        uniform mat4 model;

        flat out vec3 v_color;
        out vec2 vs_tcoords;
        void main()
        {
            gl_Position = viewProjection * model * vec4(position, 0.0, 1.0);
            vs_tcoords = tex_coords;
            
            v_color = vec3(0.1, 0.1, 0.1);
            if(gl_VertexID % 2 == 0) {
                v_color = vec3(0.9, 0.9, 0.9);
            }
            
            if(gl_VertexID == selected_vertex) {
                v_color = vec3(0.9, 0.5, 0.1);
            }
        }
    )";

    const std::string boardFragShader = R"(
        #version 430 core
        
        layout(binding = 0) uniform sampler2D u_floorTexSampler;

        flat in vec3 v_color;
        in vec2 vs_tcoords;
        out vec4 color;
        void main()
        {
            color = vec4(v_color, 0.0) * texture(u_floorTexSampler, vs_tcoords);
        }
    )";

    const std::string cubeFragShader = R"(
        #version 430 core
        
        layout(binding = 1) uniform samplerCube uTexture;

        flat in vec3 v_color;
        in vec3 vs_position;
        out vec4 color;
        void main()
        {
            color = vec4(v_color, 1.0) * texture(uTexture, vs_position);
        }
    )";

    const std::string cubeVertShader = R"(
        #version 430 core

        layout(location = 0) in vec3 position;

        uniform mat4 viewProjection;
        uniform mat4 model;

        uniform int alt_color;

        flat out vec3 v_color;
        out vec3 vs_position;
        void main()
        {
            gl_Position = viewProjection * model * vec4(position, 1.0);
            v_color = vec3(0.5, 0.0, 0.5);
            vs_position = position;

            if(alt_color == 1) {
                v_color = vec3(1.0, 1.0, 1.0);
            }
        }
    )";
}

#endif // !ASSIGNMENTSHADERS_H_
