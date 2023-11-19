#ifndef LAB2APPLICATION_H_
#define LAB2APPLICATION_H_

#include <GLFWApplication.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <memory>

class Lab2Application : public GLFWApplication {
public:
	Lab2Application(std::string name, std::string version);

	// load data
	unsigned Init() override;
	// start application loop
	unsigned Run() const override;

	GLuint selectionX = 0;
	GLuint selectionY = 0;

private:
	std::shared_ptr<VertexArray> m_vertArray;
	//GLuint m_boardArray;
	GLuint m_shaderProg;
};

#endif // LAB2APPLICATION_H_
