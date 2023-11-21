#ifndef LAB3APPLICATION_H_
#define LAB3APPLICATION_H_

#include <GLFWApplication.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <memory>

class Lab3Application : public GLFWApplication {
public:
	Lab3Application(std::string name, std::string version);

	// load data
	unsigned Init() override;
	// start application loop
	unsigned Run() const override;

	void LoadImage(std::string& name, GLuint slot);
	void LoadCubemap(std::string& name, GLuint slot);

	GLuint selectionX = 0;
	GLuint selectionY = 0;

private:
	std::shared_ptr<VertexArray> m_vertArray;
	std::shared_ptr<Shader> m_shaderProg;

	std::shared_ptr<VertexArray> m_cube;
	std::shared_ptr<Shader> m_cubeShader;
};

#endif // LAB2APPLICATION_H_
