#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLuint* indices, GLsizei count)
	: IndexBufferID(0), Count(count)
{
	// create buffer
	glGenBuffers(1, &IndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);

	// load data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	//TODO: Make sure this buffer is not bound?
	glDeleteBuffers(1, &IndexBufferID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

