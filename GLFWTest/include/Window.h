#pragma once

#include "Renderer.h"

class Window
{
public:
	Window(int xpos, int ypos, int WIDTH, int HEIGHT, const char* TITLE);
	~Window();

	static Window& Get();

	void Update();
	bool IsClosed();
	void Delete();

	void SetWidth(int width) { Width = width; }
	void SetHeight(int height) { Height = height; }
	int GetWidth() const { return Width; }
	int GetHeight()const { return  Height; }
	GLFWwindow* GetWindow() const { return window; }

private:
	GLFWwindow* window = nullptr;
	int Width = 0, Height = 0;
};

