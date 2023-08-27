#include "Camera.h"

Camera::Camera(GLFWwindow* window, unsigned int width, unsigned int height, float fov, float nClip, float fClip)
	:window(window), Width(width), Height(height), fov(fov), nClip(nClip), fClip(fClip)
{
	Position = glm::vec3(0.0f, 0.0f, 1.0f);
	Forward = glm::vec3(0.0f, 0.0f, -1.0f);
	Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
}

void Camera::Resize(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;
}

void Camera::Update(float dt)
{
	glm::vec3 Right = glm::normalize(glm::cross(Forward, Up));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += Forward * speed * dt;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position -= Forward * speed * dt;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += Right * speed * dt;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position -= Right * speed * dt;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		Position += Up * speed * dt;
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		Position -= Up * speed * dt;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = 1.5f;
	else speed = 5.0f;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick)
		{
			glfwSetCursorPos(window, (Width / 2), (Height / 2));
			firstClick = false;
		}

		double x, y;

		glfwGetCursorPos(window, &x, &y);

		float rotX = sensetivity * 10000 * (float)(x - Width / 2) / Width * dt;
		float rotY = sensetivity * 10000 * (float)(y - Height / 2) / Height * dt;
		pitch += -rotY;

		if (pitch < 85 && pitch > -85)
			Orientation = glm::rotate(Orientation, glm::radians(-rotY), Right);
		else
			pitch += rotY;
		
		Orientation = glm::rotate(Orientation, glm::radians(-rotX), Up);
		Forward = glm::rotate(Forward, glm::radians(-rotX), Up);
		glfwSetCursorPos(window, (Width / 2), (Height / 2));
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
	
	View = glm::lookAt(Position, Position + Orientation, Up);
	Projection = glm::perspective(glm::radians(fov), (float)Width / Height, nClip, fClip);
}
