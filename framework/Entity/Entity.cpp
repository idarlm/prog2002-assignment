#include <logger.h>
#include <RenderCommands.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"

using namespace glm;

Entity::Entity(
	std::shared_ptr<VertexArray> vertArray,
	std::shared_ptr<Shader> shader) 
	: id(count++), vertexArray(vertArray), shader(shader)
{
	recalculateMatrix();
}

Entity::~Entity()
{
	--count;
}

void Entity::recalculateMatrix() 
{
	matrix = mat4(1.f);
	matrix = translate(matrix, position);

	matrix = rotate(matrix, rotation, rotationAxis);

	matrix = glm::scale(matrix, this->scale);
}

void Entity::SetEulerAngles(float x, float y, float z)
{
	matrix = mat4(1.f);
	matrix = translate(matrix, position);

	matrix = rotate(matrix, radians(z), vec3(0.0f, 0.0f, 1.0f));
	matrix = rotate(matrix, radians(y), vec3(0.0f, 1.0f, 0.0f));
	matrix = rotate(matrix, radians(x), vec3(1.0f, 0.0f, 0.0f));

	matrix = glm::scale(matrix, this->scale);
}

void Entity::Update(float dt)
{
	shader->Bind();	
	RenderCommands::DrawIndex(vertexArray);
}

std::shared_ptr<Entity> Entity::MakeEntity(
	std::shared_ptr<VertexArray> vertArray,
	std::shared_ptr<Shader> shader)
{
	return std::make_shared<Entity>(vertArray, shader);
}