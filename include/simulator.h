#pragma once
#include "framebuffer.h"
#include "loadshaders.h"
#include <GL/glew.h>

class Simulator {
public:
  GLuint renderProgram, advectProgram, diffuseProgram, pressureProgram,
      projectProgram, vertexArray;
  Framebuffer *fb[2];
  Simulator(int width, int height);
  int width, height;
  void render();
  void compute(int iterations);
  void setPixel(float x, float y, void *val);
  void swapBuffers();
  void setMousePos(float x, float y);
  void setForceVector(float x, float y);
};