#ifndef LAB1_SHADERS_H
#define LAB1_SHADERS_H

#include <string>

namespace Shader{
    // triangle shaders
    const std::string triVertexShaderSrc = R"(
        #version 430 core

        layout(location = 0) in vec2 position;

        void main()
        {
            gl_Position = vec4(position, 0.0, 1.0);
        }
    )";

    const std::string triFragmentShaderSrc = R"(
        #version 430 core
        
        out vec4 color;
        void main()
        {
            color = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )";

    const std::string sqrVertexShaderSrc = R"(
        #version 430 core

        layout(location = 0) in vec2 position;
        layout(location = 1) in vec3 color;

        out vec4 v_Color;
        void main()
        {
            gl_Position = vec4(position, 0.0, 1.0);
            v_Color = vec4(color, 1.0);
        }
    )";

    const std::string sqrFragmentShaderSrc = R"(
        #version 430 core
        
        in vec4 v_Color;
        out vec4 color;
        void main()
        {
            color = v_Color;
        }
    )";
}

#endif