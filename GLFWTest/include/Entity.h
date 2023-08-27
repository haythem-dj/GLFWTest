#pragma once

#include "Camera.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
};

class Entity
{
public:
	Entity();
	~Entity();

	bool LoadFromFile(const char* path);
	void Update();

	void SetVertices(const std::vector<Vertex>& vertices);
	void SetIndecies(const std::vector<unsigned int>& indecies);
	void AddTexture(const char* path, int target, int slot, int pixelType);

	void SendUniforms(ShaderProgram& shader);

	void Bind();
	void Unbind();
	void Delete();

	unsigned int GetTextureID(int index) { return textures[index].GetID(); }
	int GetIndeciesCount() { return indeciesCount; }

	void SetPosition(glm::vec3 Position);
	void SetRotation(glm::vec3 Rotation);
	void SetScale(glm::vec3 Scale);

	void IncreasePosition(glm::vec3 dPosition);
	void IncreaseRotation(glm::vec3 dRotation);
	void IncreaseScale(glm::vec3 dScale);

	const glm::vec3& GetPosition() const { return Position; }
	const glm::vec3& GetRotation() const { return Rotation; }
	const glm::vec3& GetScale() const { return Scale; }

	void SetShininess(float shininess) { this->shininess = shininess; }

private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
	std::vector<Texture> textures;

	int indeciesCount = 0;

	glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

	glm::mat4 ModelMatrix = glm::mat4(1.0f);

	float shininess = 32.0f;
};

