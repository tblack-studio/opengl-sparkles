#pragma once
#include <glm/glm.hpp>

class Frame
{
public:
		Frame(glm::vec2 texSpritePos,
				glm::vec2 texSpriteSize);
		glm::vec2 getSpritePosition();
		glm::vec2 getSpriteSize();
private:
		glm::vec2 texSpritePos;
		glm::vec2 texSpriteSize;
};

