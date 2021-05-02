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
#include <chrono>
#include <math.h>
#include "simulator.h"
#include "player.h"
#include "rng.h"
#include "raycaster.h"
#include "screen.h"

using namespace std;
using namespace glm;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<float> fsec;

//resolution of window in pixels
int RESX = 720;
int RESY = 720;

GLFWwindow* window;
bool closed = false, paused = true;
Simulator* sim;
Player* player;
vec2 mouse;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	if (key == GLFW_KEY_ESCAPE) closed = true;

    if (key == GLFW_KEY_P && action == GLFW_PRESS) paused ^= 1;

    if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS) player->mov[0] = true;
		if (action == GLFW_RELEASE) player->mov[0] = false;
	}
	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS) player->mov[1] = true;
		if (action == GLFW_RELEASE) player->mov[1] = false;
	}
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS) player->mov[2] = true;
		if (action == GLFW_RELEASE) player->mov[2] = false;
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS) player->mov[3] = true;
		if (action == GLFW_RELEASE) player->mov[3] = false;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		player->jump();
	}
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	//vec2 diff(xpos - mouse.x, ypos - mouse.y);
	//player->rotate(diff);
	mouse = vec2(xpos, ypos);
	player->rotate(mouse);
	//std::cout << "mouse x: " << xpos << ", y: " << ypos << "\n";
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	return 0;
}

int main(void) {
	if (init() == -1) return -1;
	sim = new Simulator(256, 256);
    player = new Player();
	Raycaster raycaster;
	raycaster.setResolution(RESX, RESY);
    Framebuffer ray_fb1(RESX, RESY, GL_RGBA, GL_REPEAT, GL_LINEAR);
    Framebuffer ray_fb2(RESX, RESY, GL_RGBA, GL_REPEAT, GL_LINEAR);
    Screen screen("shaders/screen/blend.glsl");

    ray_fb1.bind();
    player->move();
    raycaster.render(player->getModel());
    ray_fb1.unbind();  
    auto t0 = Time::now();
	while (!glfwWindowShouldClose(window) && !closed) {
		glClear(GL_COLOR_BUFFER_BIT);
        auto t1 = Time::now();
		fsec t = t1 - t0;
        
        if (!paused) sim->compute();
        ray_fb1.bind();
        player->move();
        raycaster.render(player->getModel());
        ray_fb1.unbind(); 
        sim->advect(screen.fb, &ray_fb2);
        float blend_amount = 0.99f * (0.5f * sinf(0.05f * t.count()) + 0.5f);
        screen.blend(&ray_fb1, &ray_fb2, blend_amount);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}