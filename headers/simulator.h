#pragma once
#include <GL/glew.h>
#include "loadshaders.h"
#include "framebuffer.h"

class Simulator {
public:
    GLuint renderProgram, simProgram, vertexArray;
    Framebuffer *fb[2];
    Simulator(int width, int height);
    int width, height;
    void render();
    void compute();
    void setPixel(float x, float y, void *val);
};