#include <logger.h>
#include "Entity.h"

Entity::Entity(
	std::shared_ptr<VertexBuffer> vertexBuffer, 
	std::shared_ptr<IndexBuffer> indexBuffer, 
	std::shared_ptr<Shader> shader) 
	: id(count++), vertexArray(std::make_shared<VertexArray>()), shader(shader)
{
	vertexArray->AddVertexBuffer(vertexBuffer);
	vertexArray->SetIndexBuffer(indexBuffer);

	recalculateMatrix();
}

Entity::~Entity()
{

}

void Entity::recalculateMatrix() 
{
	Log::error("Entity", "recalculateMatrix() not implemented");
}

static std::shared_ptr<Entity> MakeEntity(
	std::shared_ptr<VertexBuffer> vertexBuffer,
	std::shared_ptr<IndexBuffer> indexBuffer,
	std::shared_ptr<Shader> shader)
{
	return std::make_shared<Entity>(vertexBuffer, indexBuffer, shader);
}