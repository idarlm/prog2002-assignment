#include "VertexArray.h"
#include "ShaderDataTypes.h"
#include <iostream>

VertexArray::VertexArray() 
	: m_vertexArrayID(0), m_attribCount(0)
{
	// generate vertex array
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
}

VertexArray::~VertexArray() 
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_vertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	// store a new shared pointer that is scoped to the VertexArray lifetime.
	// this prevents a buffer from being deleted when it is still in use.
	VertexBuffers.push_back(vertexBuffer);
	vertexBuffer->Bind();
	auto layout = vertexBuffer->GetLayout();
	auto attribs = layout.GetAttributes();
	for each (auto a in attribs)
	{
		auto i = m_attribCount++;
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			i,
			ShaderDataTypeComponentCount(a.Type),
			ShaderDataTypeToOpenGLBaseType(a.Type),
			a.Normalized,
			layout.GetStride(),
			(void*)a.Offset
		);
	}
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	IdxBuffer = indexBuffer;
}