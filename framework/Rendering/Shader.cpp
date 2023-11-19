#include "Shader.h"
#include <vector>
#include <logger.h>

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    auto VertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!CompileShader(VertexShader, vertexSrc))
    {
        glDeleteShader(VertexShader);
        throw std::runtime_error("Failed to compile shader");
    }

    auto FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!CompileShader(FragmentShader, fragmentSrc))
    {
        glDeleteShader(VertexShader);
        glDeleteShader(FragmentShader);
        throw std::runtime_error("Failed to compile shader");
    }

    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);

    glLinkProgram(ShaderProgram);
    glUseProgram(ShaderProgram);

    // cleanup
    glDetachShader(ShaderProgram, VertexShader);
    glDetachShader(ShaderProgram, FragmentShader);
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(ShaderProgram);
}

void Shader::Bind() const
{
    glUseProgram(ShaderProgram);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& vector)
{
    auto location = glGetUniformLocation(ShaderProgram, name.c_str());
    glProgramUniform2f(ShaderProgram, location, vector.x, vector.y);
}

GLint Shader::GetUniformLocation(const GLchar* name)
{
    return glGetUniformLocation(ShaderProgram, name);
}

bool Shader::CompileShader(GLuint shader, const std::string& shaderSrc)
{
    // compile shaders
    auto src = shaderSrc.c_str();
    glShaderSource(shader, 1, &src, 0);
    glCompileShader(shader);

    // check for errors
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        // Log error info
        Log::error("Shader", "Failed to compile shader: ", infoLog.data());
        return false;
    }
    return true;
}