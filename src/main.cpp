#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <iostream>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "simulator.h"

using namespace std;
using namespace glm;

//resolution of window in pixels
int RESX = 720;
int RESY = 720;

GLFWwindow* window;
bool closed = false, paused = true;
Simulator* sim;
vec2 mouse;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	if (key == GLFW_KEY_ESCAPE) closed = true;

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) paused ^= 1;

    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        float val[4] = {0.0, 0.0, 0.0, 1.0};
        sim->setPixel(mouse.x / RESX, 1.0f - mouse.y / RESY, (void*)&val);
    }
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	mouse = vec2(static_cast<float>(xpos), static_cast<float>(ypos));
}

int init() {
	// Initialise GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(RESX, RESY, "Test", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// Initialize GLEW
	//glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	//don't need depth test for 2d rendering
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	int error = glGetError();

	if (error != GL_NO_ERROR) {
		cout << "OpenGL error: " << error << "\n";
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorCallback);

	return 0;
}

int main(void) {
	if (init() == -1) return -1;
	sim = new Simulator(256, 256);
	while (!glfwWindowShouldClose(window) && !closed) {
		glClear(GL_COLOR_BUFFER_BIT);
        if (!paused) sim->compute();
		sim->render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}