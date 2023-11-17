#ifndef LAB2APPLICATION_H_
#define LAB2APPLICATION_H_

#include <GLFWApplication.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>

class Lab2Application : public GLFWApplication {
public:
	Lab2Application(std::string name, std::string version);

	// load data
	unsigned Init() override;
	// start application loop
	unsigned Run() const override;

private:
	VertexBuffer* m_boardVerts;
	IndexBuffer* m_indexBuffer;
	GLuint m_boardArray;
	GLuint m_shaderProg;
};

#endif // LAB2APPLICATION_H_
