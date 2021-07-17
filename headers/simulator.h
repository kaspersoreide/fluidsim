#pragma once
#include <GL/glew.h>
#include "loadshaders.h"
#include "framebuffer.h"

class Simulator {
public:
    GLuint renderProgram, advectProgram, diffuseProgram, 
        pressureProgram, projectProgram, advectorProgram, warpProgram, vertexArray;
    Framebuffer *fb[2];
    Framebuffer *warp_fb[2];
    Simulator(int width, int height);
    int width, height;
    void render();
    void compute(int iterations);
    void advect(Framebuffer* back, Framebuffer* front);
    void setPixel(float x, float y, void *val);
    void swapBuffers(Framebuffer* fb1, Framebuffer* fb2);
};