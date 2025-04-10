
#include <lib/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <stdio.h>
#include <AL/al.h>
#include <AL/alc.h>

#include "renderer.hpp"
#include "sound/soundObject.h"
#include "camera.hpp"

void glfwErrorCallback(int code, const char* description) {
	printf("[GLFW] %s\n", description);
}

void handleInput(GLFWwindow* window, Renderer& renderer) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		renderer.getCamera().moveForward(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		renderer.getCamera().moveBackward(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		renderer.getCamera().moveLeft(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		renderer.getCamera().moveRight(0.5f);
	}
}

int main() {

	// initialize the GLFW library, needs to be called once
	glfwInit();

	// set a global GLFW error handle, will notify us if we use GLFW incorectly
	glfwSetErrorCallback(glfwErrorCallback);

	// tell GLFW we want to use OpenGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	// OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // use OpenGL Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window, returns a handle we can use to refere to the created window
	GLFWwindow* glfw_window = glfwCreateWindow(400, 600, "Hello OpenGL", nullptr, nullptr);

	// this is needed so that GLAD knows about our window
	glfwMakeContextCurrent(glfw_window);

	// now that we have a window load OpenGL (as in, load function pointers from driver)
	gladLoadGL();




	// see renderer.hpp
	Renderer renderer(400,600);
	SoundObject soundObject;
	soundObject.initializationTest();
	// execute the loop as long as the close button has not been pressed
	while (!glfwWindowShouldClose(glfw_window)) {

		// ask the window system if there are any peding events and dispatch them to handlers
		glfwPollEvents();

		handleInput(glfw_window, renderer);
		// draw the scene
		renderer.draw();
		// swap back and front buffer
		glfwSwapBuffers(glfw_window);

	}

	// free all OpenGL resources
	renderer.close();

	// close the window
	glfwDestroyWindow(glfw_window);

	// uninitilize GLFW
	glfwTerminate();

	return 0;

}
