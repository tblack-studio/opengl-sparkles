#include "ortho_camera.h"

OrthoCamera::OrthoCamera(float screenWidth, float screenHeight)
{
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		this->projection = glm::ortho(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);
}

void OrthoCamera::update()
{
		this->view = glm::lookAt(glm::vec3(.0f, .0f, .1f), glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, 1.0f, .0f));
}

glm::mat4 OrthoCamera::getProjection()
{
		return this->projection;
}

glm::mat4 OrthoCamera::getView()
{
		return this->view;
}
