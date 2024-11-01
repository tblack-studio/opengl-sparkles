#pragma once
#include "camera.h"
class OrthoCamera :
		public Camera
{
public: OrthoCamera(float screenWidth, float screenHeight);
			void update();
			glm::mat4 getProjection() override;
			glm::mat4 getView() override;
private:
		float screenWidth, screenHeight;
		glm::mat4 projection;
		glm::mat4 view;
};

