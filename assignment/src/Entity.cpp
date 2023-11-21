#include <logger.h>
#include <RenderCommands.h>
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
	--count;
}

void Entity::recalculateMatrix() 
{
	Log::error("Entity", "recalculateMatrix() not implemented");
}

void Entity::Update(float dt)
{
	shader->Bind();	
	RenderCommands::DrawIndex(vertexArray);
}

std::shared_ptr<Entity> Entity::MakeEntity(
	std::shared_ptr<VertexBuffer> vertexBuffer,
	std::shared_ptr<IndexBuffer> indexBuffer,
	std::shared_ptr<Shader> shader)
{
	return std::make_shared<Entity>(vertexBuffer, indexBuffer, shader);
}