#pragma once

#include "Scene.h"

class Renderer
{
public:
	void Render(Entity& entity, ShaderProgram& program, Camera& camera);
	void Render(Scene& scene, ShaderProgram& program, Camera& camera);
};

