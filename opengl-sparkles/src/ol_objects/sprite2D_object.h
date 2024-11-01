#pragma once
#include "ol_object.h"
#include "../camera.h"
#include "../texture.h"
#include "../tex_sprite.h"

class Sprite2DObject :
		public OlObject
{
public:
		Sprite2DObject();
		void render() override;
		void destroy() override;
		void setCameraPtr(Camera* cameraPtr);
		void setPosition(glm::vec3 position);
		void setSize(glm::vec2 size);
		void setTexturePtr(Texture* texturePtr);
		void setSpriteTexture(glm::vec2 position, glm::vec2 size);
		void setTexSprite();
protected:
		void prepareRender() override;
private:
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
		std::unique_ptr<Shader> shader;
		Camera* cameraPtr;
		glm::vec3 position;
		glm::vec2 size;
		Texture* texturePtr;
		glm::vec2 texPosition;
		glm::vec2 texSize;
		TexSprite texSprite;
};

