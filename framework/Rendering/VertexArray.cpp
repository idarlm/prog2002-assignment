#include "VertexArray.h"
#include "ShaderDataTypes.h"

VertexArray::VertexArray() : m_vertexArrayID(0) 
{
	// generate vertex array
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
}

VertexArray::~VertexArray() {}

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
	vertexBuffer->Bind();
	auto layout = vertexBuffer->GetLayout();
	auto attribs = layout.GetAttributes();
	for each (auto a in attribs)
	{
		auto i = m_attribCount++;
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			i,
			a.Size,
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