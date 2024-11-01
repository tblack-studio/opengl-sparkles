#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <iostream>
#include "src/ol_objects/animation.h"
#include "src/ortho_camera.h"
#include "src/ol_objects/sprite2D_object.h"
#include "src/texture.h"
#include "src/ol_objects/frame.h"


void framebuffer_size_callback(const GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// glfw window creation
		// --------------------
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Sparkes", nullptr, nullptr);
		if (window == nullptr)
		{
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun)framebuffer_size_callback);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return -1;
		}
		Texture texture("textures/spritesheet.png", 1);
		texture.load();

		auto spriteSize = 64.0f;

		OrthoCamera camera(SCR_WIDTH, SCR_HEIGHT);
		Sprite2DObject sprite;
		sprite.setCameraPtr(&camera);
		sprite.setTexturePtr(&texture);
		sprite.setPosition(glm::vec3(SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f, 0));
		sprite.setSize(glm::vec2(spriteSize, spriteSize));
		sprite.setSpriteTexture(glm::vec2(0, 0), glm::vec2(spriteSize, spriteSize));
		sprite.setupUV();

		Animation animation(0.15f);
		animation.setLoop(true);
		animation.setSpriteRenderer(&sprite);

		animation.addFrame(Frame(glm::vec2(0, 0), glm::vec2(spriteSize, spriteSize)));
		animation.addFrame(Frame(glm::vec2(spriteSize, 0), glm::vec2(spriteSize, spriteSize)));
		animation.addFrame(Frame(glm::vec2(2 * spriteSize, 0), glm::vec2(spriteSize, spriteSize)));
		animation.addFrame(Frame(glm::vec2(3 * spriteSize, 0), glm::vec2(spriteSize, spriteSize)));
		animation.addFrame(Frame(glm::vec2(0, spriteSize), glm::vec2(spriteSize, spriteSize)));
		animation.addFrame(Frame(glm::vec2(spriteSize, spriteSize), glm::vec2(spriteSize, spriteSize)));

		animation.start();
		// render loop
		// -----------
		while (!glfwWindowShouldClose(window))
		{
				camera.update();
				animation.update();

				// input
				// -----
				processInput(window);

				// render
				// ------
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				// render container
				//sprite.render();
				animation.render();

				// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
				// -------------------------------------------------------------------------------
				glfwSwapBuffers(window);
				glfwPollEvents();
		}

		// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------


		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
		return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
				return;
		}
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(const GLFWwindow*, int width, int height)
{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glad_glViewport(0, 0, width, height);
}