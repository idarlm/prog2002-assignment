#ifndef SHADER_H_

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);

	GLint GetUniformLocation(const GLchar* name);

private:
	// I have decided to alter the implementation of this class
	// to allow for easier cleanup in case of compilation failure.

	GLuint ShaderProgram;
	bool CompileShader(GLuint shader, const std::string& shaderSrc);
};

#endif // !SHADER_H_
