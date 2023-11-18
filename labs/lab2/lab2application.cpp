#include <logger.h>
#include <glad/glad.h>
#include <GeometricTools.h>
#include <ShaderDataTypes.h>
#include "lab2application.h"
#include "shaders.h"

Lab2Application::Lab2Application(std::string name, std::string version) 
    : GLFWApplication(name, version) {}

unsigned Lab2Application::Init() 
{
    if (GLFWApplication::Init() != GLFWApplication::OK) 
    {
        Log::error("Lab2Application", "Failed to init GLFWApplication.");
        return 1;
    }

    // create VAO
    m_vertArray = std::make_shared<VertexArray>();

    // create VBO
    auto verts = GeometricTools::UnitGridGeometry2D(8, 8);
    auto vbuff = std::make_shared<VertexBuffer>(verts.data(), verts.size() * sizeof(float));
    vbuff->SetLayout(
        BufferLayout({
            {ShaderDataType::Float2, "position"}
        })
    );

    // create EBO
    auto indices = GeometricTools::UnitGridTopologyTriangles(8, 8);   
    auto ibuff = std::make_shared<IndexBuffer>(indices.data(), indices.size());

    m_vertArray->AddVertexBuffer(vbuff);
    m_vertArray->SetIndexBuffer(ibuff);

    // compile shaders
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    auto vss = Shader::sqrVertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vss, 0);
    glCompileShader(vertexShader);

    // this snippet is borrowed from the Khronos OpenGL wiki:
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        Log::info("Shader compilation", infoLog.data());

        // In this simple program, we'll just leave
        return 1;
    }
    // source: https://www.khronos.org/opengl/wiki/Shader_Compilation#Shader_error_handling

    auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    auto fss = Shader::sqrFragmentShaderSrc.c_str();
    glShaderSource(fragShader, 1, &fss, 0);
    glCompileShader(fragShader);

    auto shaderProg = glCreateProgram();
    glAttachShader(shaderProg, vertexShader);
    glAttachShader(shaderProg, fragShader);
    glLinkProgram(shaderProg);
    glUseProgram(shaderProg);

    //glDetachShader(shaderProg, vertexShader);
    //glDetachShader(shaderProg, fragShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    m_shaderProg = shaderProg;

    return 0;
}

unsigned Lab2Application::Run() const 
{
    Log::info("Lab2Application", "Starting application loop");

    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();

        // clear window
        glClearColor(0.1f, 0.25f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw board
        m_vertArray->Bind();
        glUseProgram(m_shaderProg);
        glDrawElements(GL_TRIANGLES, m_vertArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

        // display new frame
        glfwSwapBuffers(window);
    }

    return 0;
}
