#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertex_path, const char* fragment_path)
{
	ID = CreateProgram(LoadShader(vertex_path), LoadShader(fragment_path));
}

void ShaderProgram::Activate()
{
	glUseProgram(ID);
}

void ShaderProgram::Deactivate()
{
	glUseProgram(0);
}

void ShaderProgram::Delete()
{
	glDeleteProgram(ID);
}

std::string ShaderProgram::LoadShader(const std::string& file_path)
{
	std::ifstream stream(file_path);

	std::string line;
	std::stringstream ss;
	while (getline(stream, line))
	{
		ss << line << "\n";
	}

	stream.close();

	return ss.str();
}

unsigned int ShaderProgram::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
		std::cout << message << std::endl;
	}

	return shader;
}

unsigned int ShaderProgram::CreateProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	ID = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(ID, vs);
	glAttachShader(ID, fs);

	glLinkProgram(ID);
	glValidateProgram(ID);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return ID;
}
