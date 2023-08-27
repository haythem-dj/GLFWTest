#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddEntity(const Entity& entity)
{
	entities.push_back(entity);
}

void Scene::Clear()
{
	for (Entity& entity : entities)
	{
		entity.Delete();
	}
	entities.clear();
}
