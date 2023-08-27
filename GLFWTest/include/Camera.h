#pragma once

#include "Texture.h"

class Camera
{
public:
	Camera(GLFWwindow* window, unsigned int width, unsigned int height, float fov, float nClip, float fClip);

	void Resize(unsigned int width, unsigned int height);
	void Update(float dt);

	void SetPosition(glm::vec3 position) { Position = position; }
	void SetForwrad(glm::vec3 forward) { Forward = forward; }

	const glm::vec3& GetPosition() const { return Position; }
	const glm::vec3& GetOrientation() const { return Orientation; }
	const glm::mat4& GetView() const { return View; }
	const glm::mat4& GetProjection() const { return Projection; }

private:
	GLFWwindow* window;

	unsigned int Width = 0;
	unsigned int Height = 0;

	float fov = 0.0f;
	float nClip = 0.0f;
	float fClip = 0.0f;

	bool firstClick = true;

	float speed = 5.0f;
	float sensetivity = 4.0f;
	float pitch = 0;

	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Orientation = glm::vec3(0.0f);
	glm::vec3 Forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 View = glm::mat4(1.0f);
	glm::mat4 Projection = glm::mat4(1.0f);
};

