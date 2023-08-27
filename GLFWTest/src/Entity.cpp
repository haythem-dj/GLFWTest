#include "Entity.h"

Entity::Entity()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
}

Entity::~Entity()
{
}

bool Entity::LoadFromFile(const char* path)
{
	std::ifstream file(path);
	std::string line;

	if (!file.is_open())
		return false;

	std::vector<Vertex> verts = {};
	std::vector<unsigned int> indes = {};

	std::vector<glm::vec3> positions = {};
	std::vector<glm::vec3> normals = {};
	std::vector<glm::vec2> textures = {};

	unsigned int index = 0;
	while (getline(file, line))
	{
		std::stringstream s;
		char junk;

		s << line;

		if (line.rfind("v ", 0) == 0)
		{
			glm::vec3 position;
			s >> junk >> position.x >> position.y >> position.z;
			positions.push_back(position);
		}
		else if (line.rfind("vt", 0) == 0)
		{
			glm::vec2 texture;
			s >> junk >> junk >> texture.x >> texture.y;
			textures.push_back(texture);
		}
		else if (line.rfind("vn", 0) == 0)
		{
			glm::vec3 normal;
			s >> junk >> junk >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (line.rfind("f", 0) == 0)
		{
			s >> junk;
			for (int i = 0; i < 3; i++)
			{
				Vertex vert;
				unsigned int v = 0, t = 0, n = 0;
				s >> v >> junk >> t >> junk >> n;
				if (positions.size() > 0)
					vert.position = positions[v - 1];
				if (textures.size() > 0)
					vert.texture = textures[t - 1];
				if (normals.size() > 0)
					vert.normal = normals[n - 1];

				verts.push_back(vert);
				indes.push_back(index);

				index++;
			}
		}
	}

	file.close();

	SetVertices(verts);
	SetIndecies(indes);

	return true;
}

void Entity::Update()
{
	ModelMatrix = glm::translate(ModelMatrix, Position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.x), { 1.0f, 0.0f, 0.0f });
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.y), { 0.0f, 1.0f, 0.0f });
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.z), { 0.0f, 0.0f, 1.0f });
	ModelMatrix = glm::scale(ModelMatrix, Scale);
}

void Entity::SetVertices(const std::vector<Vertex>& vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(6 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Entity::SetIndecies(const std::vector<unsigned int>& indecies)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecies.size() * sizeof(unsigned int), indecies.data(), GL_STATIC_DRAW);
	indeciesCount = (int)indecies.size();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Entity::AddTexture(const char* path, int target, int slot, int pixelType)
{
	Texture tex;
	tex.Load(path, target, slot, pixelType);
	textures.push_back(tex);
}

void Entity::SetPosition(glm::vec3 Position)
{
	this->Position = Position;
	ModelMatrix = glm::mat4(1.0f);
	Update();
}

void Entity::SetRotation(glm::vec3 Rotation)
{
	this->Rotation = Rotation;
	ModelMatrix = glm::mat4(1.0f);
	Update();
}

void Entity::SetScale(glm::vec3 Scale)
{
	this->Scale = Scale;
	ModelMatrix = glm::mat4(1.0f);
	Update();
}

void Entity::IncreasePosition(glm::vec3 dPosition)
{
	this->Position += dPosition;
	ModelMatrix = glm::mat4(1.0f);
	Update();
}

void Entity::IncreaseRotation(glm::vec3 dRotation)
{
	this->Rotation += dRotation;
	ModelMatrix = glm::mat4(1.0f);
	Update();
}

void Entity::IncreaseScale(glm::vec3 dScale)
{
	this->Scale += dScale;
	ModelMatrix = glm::mat4(1.0f);
	Update();
}

void Entity::SendUniforms(ShaderProgram& shader)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniform1i(glGetUniformLocation(shader.GetID(), "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(shader.GetID(), "material.specular"), 1);
	glUniform1f(glGetUniformLocation(shader.GetID(), "material.shininess"), shininess);
}

void Entity::Bind()
{
	for (Texture& tex : textures)
		tex.Bind();

	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void Entity::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);
	for (Texture& tex : textures)
		tex.Unbind();
}

void Entity::Delete()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	for (Texture& tex : textures)
		tex.Delete();
}
