#ifndef LAB2_SHADERS_H
#define LAB2_SHADERS_H

#include <string>

namespace Shader {
    const std::string sqrVertexShaderSrc = R"(
        #version 430 core

        layout(location = 0) in vec2 position;

        flat out vec3 v_color;
        void main()
        {
            gl_Position = vec4(position, 0.0, 1.0);
            
            v_color = vec3(0.1, 0.1, 0.1);
            if(gl_VertexID % 2 == 0) {
                v_color = vec3(0.9, 0.9, 0.9);
            }
        }
    )";

    const std::string sqrFragmentShaderSrc = R"(
        #version 430 core
        
        flat in vec3 v_color;
        out vec4 color;
        void main()
        {
            color = vec4(v_color, 1.0);
        }
    )";
}

#endif