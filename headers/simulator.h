#pragma once
#include <GL/glew.h>
#include "loadshaders.h"
#include "framebuffer.h"

class Simulator {
public:
    GLuint renderProgram, advectProgram, diffuseProgram, 
        pressureProgram, projectProgram, advectorProgram, vertexArray;
    Framebuffer *fb[2];
    Simulator(int width, int height);
    int width, height;
    void render();
    void compute();
    void advect(Framebuffer* target);
    void setPixel(float x, float y, void *val);
    void swapBuffers();
};