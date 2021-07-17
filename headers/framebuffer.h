#pragma once
#include "GL/glew.h"
#include "loadshaders.h"

//helper enum for different texture types
enum FramebufferType{
    FB_LINEAR_CLAMP,
    FB_NEAREST_REPEAT,
    FB_LINEAR_REPEAT
};

class Framebuffer {
public:
	Framebuffer(GLsizei width, GLsizei height, GLint internalformat, GLint wrap_method, GLint interp, GLenum type, GLenum format);
	void bind(){ glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); }
	void unbind(){ glBindFramebuffer(GL_FRAMEBUFFER, 0); }
    void draw();
	GLuint texture, depthbuffer, framebuffer;
    GLsizei width, height;
};
