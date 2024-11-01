#include "texture.h"
#include <glad.h>
#define STB_IMAGE_IMPLEMENTATION    
#include <stb_image.h>
#include <iostream>

Texture::Texture(const char* filePath, int textureNameId)
{
		this->filePath = filePath;
		this->textureNameId = textureNameId;
}

void Texture::load()
{
		// load and create a texture 
	// -------------------------		
		glGenTextures(this->textureNameId, &this->glTexture);
		glBindTexture(GL_TEXTURE_2D, glTexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps		
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		unsigned char* data = stbi_load(this->filePath, &this->width, &this->height, &this->nrChannels, 0);
		if (!data)
		{
				std::cout << "Failed to load texture" << std::endl;
				return;
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		// bind Texture
		glBindTexture(GL_TEXTURE_2D, this->glTexture);
}

/*
* texture coor is upper left based
*/
std::array<glm::vec2, 4> Texture::getSprite(glm::vec2 position, glm::vec2 size)
{
		/*
		* gl texture position is lower left based (x: 0 -> 1, y: 0 -> 1)
		*/
		auto top = 1.0f - position.y / height;
		auto bottom = top - size.y / height;

		auto left = position.x / width;
		auto right = left + size.x / width;

		return std::array<glm::vec2, 4>({
				glm::vec2(left, top),			// left upper
				glm::vec2(right, top),		// right upper
				glm::vec2(right, bottom),	// right lower
				glm::vec2(left, bottom)		// left lower
				});
}

glm::vec2 Texture::getImageSize()
{
		return glm::vec2(width, height);
}
