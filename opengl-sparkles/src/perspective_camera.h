#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

class PerspectiveCamera : public Camera
{
public: PerspectiveCamera(float screenWidth, float screenHeight);
			void update();
			glm::mat4 getProjection() override;
			glm::mat4 getView() override;
private:
		float screenWidth, screenHeight;
		glm::mat4 projection;
		glm::mat4 view;
};

