#pragma once
#include <GL/glew.h>
#include "framebuffer.h"

class Screen {
public:
GLuint vertexArray, program;
Framebuffer *fb;
Screen(const char* fragshader);
void blend(Framebuffer* fb1, Framebuffer* fb2, float amount);
void renderWarped(Framebuffer* fb, Framebuffer* warpmap);
};