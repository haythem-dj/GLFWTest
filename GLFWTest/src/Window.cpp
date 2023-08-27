#include "Window.h"

Window* Instance = nullptr;

static void Resized(GLFWwindow* window, int width, int height)
{
	Window::Get().SetWidth(width);
	Window::Get().SetHeight(height);

	glViewport(0, 0, width, height);
}

Window::Window(int xpos, int ypos, int WIDTH, int HEIGHT, const char* TITLE)
	:Width(WIDTH), Height(HEIGHT)
{
	Instance = this;

	if (!glfwInit())
	{
		std::cout << "Failed to init glfw" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create the window" << std::endl;
		return;
	}
	glfwSetWindowPos(window, xpos, ypos);

	glfwSetWindowSizeCallback(window, Resized);

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init glew" << std::endl;
		return;
	}
}

Window::~Window()
{
}

Window& Window::Get()
{
	return *Instance;
}

void Window::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Window::IsClosed()
{
	return glfwWindowShouldClose(window);
}

void Window::Delete()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	delete Instance;
}
