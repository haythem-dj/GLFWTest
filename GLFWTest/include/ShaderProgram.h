#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderProgram
{
public:
	ShaderProgram(const char* vertex_path, const char* fragment_path);
	void Activate();
	void Deactivate();
	void Delete();

	unsigned int GetID() const { return ID; }

private:
	std::string LoadShader(const std::string& file_path);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateProgram(const std::string& vertexShader, const std::string& fragmentShader);

private:
	unsigned int ID = 0;
};