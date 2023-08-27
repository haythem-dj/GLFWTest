#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_textureCoord;

out vec3 Normal;
out vec2 textureCoord;
out vec3 worldPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	vec4 position = model * vec4(in_position, 1);
	gl_Position = proj * view * position;
	Normal = mat3(transpose(inverse(model))) * in_normal;
	textureCoord = in_textureCoord;
	worldPosition = position.xyz;
}