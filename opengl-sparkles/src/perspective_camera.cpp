#include "perspective_camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glfw3.h>

PerspectiveCamera::PerspectiveCamera(float screenWidth, float screenHeight)
{
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		this->projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, .1f, 100.0f); // glm::ortho(.0f, screenWidth, .0f, screenHeight); 
}

void PerspectiveCamera::update()
{
		this->view = glm::lookAt(glm::vec3(3.0f, .0f, 5.0f), glm::vec3(0.0f, 0.0f, .0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 PerspectiveCamera::getProjection()
{
		return projection;
}

glm::mat4 PerspectiveCamera::getView()
{
		return view;
}
