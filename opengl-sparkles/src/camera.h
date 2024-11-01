#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
		virtual glm::mat4 getProjection() {
				return glm::mat4();
		}
		virtual glm::mat4 getView() {
				return glm::mat4();
		}
};