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
    GLFWApplication::Init();

    // create VAO
    glGenVertexArrays(1, &m_boardArray);
    glBindVertexArray(m_boardArray);

    // create VBO
    auto verts = GeometricTools::UnitGridGeometry2D(8, 8);
    m_boardVerts = new VertexBuffer(verts.data(), verts.size() * sizeof(float));

    // create EBO
    auto indices = GeometricTools::UnitGridTopologyTriangles(8, 8);   
    m_indexBuffer = new IndexBuffer(indices.data(), indices.size());

    // add vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

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
        glBindVertexArray(m_boardArray);
        glUseProgram(m_shaderProg);
        glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

        // display new frame
        glfwSwapBuffers(window);
    }

    delete m_boardVerts;
    delete m_indexBuffer;

    return 0;
}
