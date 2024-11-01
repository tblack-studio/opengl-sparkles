#include "animation.h"
#include <glfw3.h>

Animation::Animation(float frameDuration)
{
		this->frameDuration = frameDuration;
}

void Animation::update()
{
		if (!started) {
				return;
		}
		time = (float)glfwGetTime();
		activeFrameIndex = (int)(fmod((time - startTime), fullDuration) / frameDuration);
}

void Animation::addFrame(Frame frame)
{
		this->frames.push_back(frame);
		this->fullDuration = this->frames.size() * this->frameDuration;
}

void Animation::setSpriteRenderer(Sprite2DObject* spriteRenderer)
{
		this->spriteRenderer = spriteRenderer;
}

void Animation::render()
{
		if (!started) {
				return;
		}
		prepareRender();
		this->spriteRenderer->render();
}

void Animation::destroy()
{
}

void Animation::setLoop(bool loop)
{
		this->loop = loop;
}

bool Animation::isLoop()
{
		return this->loop;
}

void Animation::start()
{
		started = true;
		startTime = (float)glfwGetTime();
}

void Animation::prepareRender()
{
		if (!started) {
				return;
		}

		auto activeFrame = frames[activeFrameIndex];
		spriteRenderer->setSpriteTexture(activeFrame.getSpritePosition(), activeFrame.getSpriteSize());
}
