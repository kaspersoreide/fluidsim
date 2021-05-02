#pragma once
#include "glm/glm.hpp"

using namespace glm;

mat3 srotate(vec3 rot);

mat3 rotateX(float radians);
mat3 rotateY(float radians);
mat3 rotateZ(float radians);

mat4 translateR(mat3 R, vec3 p);