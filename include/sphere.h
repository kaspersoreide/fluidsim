#pragma once
#include "loadshaders.h"
#include <GL/glew.h>

class Sphere {

public:
  Sphere(int lod);
  GLuint vertShader, fragShader;
  GLuint vao;
};
