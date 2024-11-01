#pragma once

#include "ol_object.h"
#include <vector>
#include "frame.h"
#include "sprite2D_object.h"

class Animation : OlObject {
public:
		Animation(float frameDuration);
		void update();
		void addFrame(Frame frame);
		void setSpriteRenderer(Sprite2DObject* spriteRenderer);
		void render() override;
		void destroy() override;
		void setLoop(bool loop);
		bool isLoop();
		void start();
protected:
		void prepareRender() override;
private:
		float fullDuration;
		float frameDuration;
		std::vector<Frame> frames;
		Sprite2DObject* spriteRenderer;
		bool loop;
		float time;
		int activeFrameIndex;
		bool started;
		float startTime;
};