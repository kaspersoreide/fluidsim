#include "simulator.h"

Simulator::Simulator(int width, int height) : width(width), height(height) {
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

    for (int i = 0; i < 2; i++) fb[i] = new Framebuffer(width, height, FB_NEAREST_REPEAT);

    renderProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/frag.glsl");
    simProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/life.glsl");
    glUniform2f(glGetUniformLocation(simProgram, "scale"), 1.0f / width, 1.0f / height);
}

void Simulator::render() {
    glUseProgram(renderProgram);
    glBindVertexArray(vertexArray);
    glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Simulator::compute() {
    glUseProgram(simProgram);
    glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
    glBindVertexArray(vertexArray);

    fb[1]->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    fb[1]->unbind();

    //swap framebuffers
    Framebuffer *tmp = fb[1];
    fb[1] = fb[0];
    fb[0] = tmp;
}


void Simulator::setPixel(float x, float y, void *val) {
    int tx = x * width;
    int ty = y * height;
    glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, tx, ty, 1, 1, GL_RGBA, GL_FLOAT, val);
}