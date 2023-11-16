#include <glad/glad.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* vertices, GLsizei size) : m_vertexBufferID(0)
{
	// create and bind vertex buffer
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);

	// load vertex data into buffer
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	// make sure that this buffer is not bound
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// delete buffer
	glDeleteBuffers(1, &m_vertexBufferID);
}

void VertexBuffer::Bind() const 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
}

void VertexBuffer::Unbind() const 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const
{
	// make sure this buffer is bound
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);

	// load data
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
