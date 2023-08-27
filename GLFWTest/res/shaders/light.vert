#version 330 core

layout(location = 0) in vec4 in_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * in_position;
}