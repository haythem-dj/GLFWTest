#pragma once

#include "ShaderProgram.h"

class Texture
{
public:
	Texture();

	void Load(const char* path, int target, int slot, int pixelType);
	void Bind();
	void Unbind();
	void Delete();

	unsigned int GetID() const { return ID; }

private:
	unsigned int ID = 0;
	int target = 0;
	int slot = 0;
};

