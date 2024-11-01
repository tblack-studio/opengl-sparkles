#include "sprite2D_object.h"
#include <vector>

Sprite2DObject::Sprite2DObject()
{
		shader = std::make_unique<Shader>("shaders/with_camera_transform_position.v.glsl", "shaders/color_texture.f.glsl");
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
}

void Sprite2DObject::prepareRender() {
		auto textureInfo = this->texturePtr->getSprite(this->texPosition, this->texSize);
		auto vertexStride = 8; // 8 float values per vertex
		// set up vertex data (and buffer(s)) and configure vertex attributes	
		auto halfWidth = this->size.x / 2.0f;
		auto halfHeight = this->size.y / 2.0f;

		std::vector<float> vertices = {
				// positions																// colors           // texture coords
				-halfWidth, halfHeight, 0,									1,0,0,							textureInfo[0].x, textureInfo[0].y, // left top
				halfWidth, halfHeight, 0,										1,0,0,							textureInfo[1].x, textureInfo[1].y, // right top
				halfWidth, -halfHeight, 0,									1,0,0,							textureInfo[2].x, textureInfo[2].y, // right bottom
				-halfWidth, -halfHeight, 0,									1,0,0,							textureInfo[3].x, textureInfo[3].y, // left bottom
		};

		//std::vector<float> vertices = {
		//		// positions																// colors           // texture coords: https://devcry.heiho.net/html/2017/20170930-opengl-spritesheet.html
		//		-halfWidth, halfHeight, 0,									1,0,0,							texSprite.tx, texSprite.ty,
		//		halfWidth, halfHeight, 0,										1,0,0,							texSprite.tx + texSprite.tw, texSprite.ty,
		//		halfWidth, -halfHeight, 0,									1,0,0,							texSprite.tx, texSprite.ty + texSprite.th,
		//		-halfWidth, -halfHeight, 0,									1,0,0,							texSprite.tx + texSprite.tw, texSprite.ty + texSprite.th,
		//};

		std::vector<unsigned int> indices = {
				0, 1, 3, // first triangle
				1, 2, 3  // second triangle
		};
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float), (void*)nullptr);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
}

void Sprite2DObject::render() {
		prepareRender();
		shader->use(); // using shader
		auto transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, this->position);
		//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		shader->use(); // using shader
		shader->setMat4("transform", transform);
		shader->setMat4("projection", cameraPtr->getProjection());
		shader->setMat4("view", cameraPtr->getView());

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Sprite2DObject::destroy()
{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
}

void Sprite2DObject::setCameraPtr(Camera* cameraPtr)
{
		this->cameraPtr = cameraPtr;
}

void Sprite2DObject::setPosition(glm::vec3 position)
{
		this->position = position;
}

void Sprite2DObject::setSize(glm::vec2 size)
{
		this->size = size;
}

void Sprite2DObject::setTexturePtr(Texture* texturePtr)
{
		this->texturePtr = texturePtr;
}

void Sprite2DObject::setSpriteTexture(glm::vec2 position, glm::vec2 size)
{
		this->texPosition = position;
		this->texSize = size;
}

void Sprite2DObject::setTexSprite()
{
		texSprite.h = texSize.y;
		texSprite.w = texSize.x;
		texSprite.x = texPosition.x;
		texSprite.y = texPosition.y;

		auto imgSize = texturePtr->getImageSize();

		texSprite.setTexInfo(imgSize.x, imgSize.y);
}
