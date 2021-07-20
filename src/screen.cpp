#include "screen.h"

extern int RESX;
extern int RESY;

Screen::Screen(const char* fragshader) {
    program = loadShaders("shaders/screen/vert.glsl", fragshader);
    GLuint vertexBuffer;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	GLfloat vertices[] = {
		1.0,	-1.0,	0.0,	1.0,
		1.0,	1.0,	0.0,	1.0,
		-1.0,	1.0,	0.0,	1.0,
		1.0,	-1.0,	0.0,	1.0,
		-1.0,	-1.0,	0.0,	1.0,
		-1.0,	1.0,	0.0,	1.0
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    fb = new Framebuffer(RESX, RESY, GL_RGBA, GL_REPEAT, GL_LINEAR, GL_UNSIGNED_BYTE, GL_RGBA);
}

void Screen::blend(Framebuffer* fb1, Framebuffer* fb2, float amount) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fb1->texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fb2->texture);
    fb->bind();
    glUseProgram(program);
    glUniform1f(glGetUniformLocation(program, "weight"), amount);
    glBindVertexArray(vertexArray);
    glUniform1i(glGetUniformLocation(program, "tex1"), 0);
    glUniform1i(glGetUniformLocation(program, "tex2"), 1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    fb->unbind();
    glActiveTexture(GL_TEXTURE0);
    fb->draw();
}

void Screen::renderWarped(Framebuffer* fb, Framebuffer* warpmap) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, warpmap->texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fb->texture);
    glUseProgram(program);
    glBindVertexArray(vertexArray);
    glUniform1i(glGetUniformLocation(program, "warpmap"), 0);
    glUniform1i(glGetUniformLocation(program, "img"), 1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
