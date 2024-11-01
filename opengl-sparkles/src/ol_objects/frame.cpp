#include "frame.h"

Frame::Frame(
		glm::vec2 texSpritePos,
		glm::vec2 texSpriteSize)
{
		this->texSpritePos = texSpritePos;
		this->texSpriteSize = texSpriteSize;
}

glm::vec2 Frame::getSpritePosition()
{
		return this->texSpritePos;
}

glm::vec2 Frame::getSpriteSize()
{
		return this->texSpriteSize;
}
