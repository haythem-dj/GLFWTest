#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
{

}

void Texture::Load(const char* path, int target, int slot, int pixelType)
{
	this->target = target;
	this->slot = slot;
	
	glGenTextures(1, &ID);
	Bind();

	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

	stbi_set_flip_vertically_on_load(true);

	int imgWidth, imgHeight, imgCha;
	unsigned char* image = stbi_load(path, &imgWidth, &imgHeight, &imgCha, 0);

	int format;
	if (imgCha == 3) format = GL_RGB;
	else format = GL_RGBA;

	if (image)
	{
		glTexImage2D(target, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, image);
	}
	else
	{
		std::cout << "Failed to load image " << path << std::endl;
	}

	glGenerateMipmap(target);

	stbi_image_free(image);

	Unbind();
}

void Texture::Bind()
{
	glActiveTexture(slot);
	glBindTexture(target, ID);
}

void Texture::Unbind()
{
	glBindTexture(target, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
