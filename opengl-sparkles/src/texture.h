#pragma once
#include <glm/glm.hpp>
#include <array>

class Texture
{
public:
		Texture(const char* filePath,
				int textureNameId);
		void load();
		/* from texture coordinate to gl coordinate*/
		std::array<glm::vec2, 4> getSprite(glm::vec2 position, glm::vec2 size);
		glm::vec2 getImageSize();
private:
		const char* filePath;
		int textureNameId;
		int width;
		int height;
		int nrChannels;
		unsigned int glTexture;
};

