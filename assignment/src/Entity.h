#ifndef ENTITY_H_
#define ENTITY_H_

#include <glm/glm.hpp>
#include <Shader.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <RenderCommands.h>
#include <memory>

/// <summary>
/// Entity provides a simple interface for creating and managing
/// 3d objects in the scene.
/// </summary>
class Entity
{
private:
	inline static int count = 0;
	int id;

	const std::shared_ptr<VertexArray> vertexArray;
	const std::shared_ptr<Shader> shader;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 matrix = glm::mat4(1.f);

	void recalculateMatrix();

public:
	// constructor and destructor
	Entity(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<Shader>);
	~Entity();

	// getters and setters
	void SetPosition(glm::vec3 pos) { this->position = pos; recalculateMatrix(); }
	void SetRotation(glm::vec3 rot) { this->rotation = rot; recalculateMatrix(); }
	void SetScale(glm::vec3 scale) { this->scale = scale; recalculateMatrix(); }

	int GetID() { return id; }
	glm::mat4 GetMatrix() { return matrix; };
	const std::shared_ptr<Shader> GetShader() { return shader; }
	
public:
	/// <summary>
	/// MakeEntity is a convenience constructor that returns a shared_ptr
	/// to the new Entity. Useful when needing to add many entities to a collection.
	/// </summary>
	static std::shared_ptr<Entity> MakeEntity(
		std::shared_ptr<VertexBuffer> vertexBuffer, 
		std::shared_ptr<IndexBuffer> indexBuffer,
		std::shared_ptr<Shader> shader
	);
};

#endif // !ENTITY_H_
