#pragma once

#include "Entity.h"

class Scene
{
public:
	Scene();
	~Scene();

	void AddEntity(const Entity& entity);
	
	void Clear();

	std::vector<Entity> GetEntities() const { return entities; }
private:
	std::vector<Entity> entities;

	unsigned int CurrentID = 0;
};
