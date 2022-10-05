#include "simulator.h"

extern int RESX;
extern int RESY;

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

    for (int i = 0; i < 2; i++) fb[i] = new Framebuffer(width, height, FB_LINEAR_REPEAT);

    renderProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/frag.glsl");
    advectProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/advect.glsl");
    diffuseProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/diffuse.glsl");
    pressureProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/solvepressure.glsl");
    projectProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/project.glsl");
}

void Simulator::render() {
    glUseProgram(renderProgram);
    glBindVertexArray(vertexArray);
    glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Simulator::swapBuffers() {
    //swap framebuffers
    Framebuffer *tmp = fb[1];
    fb[1] = fb[0];
    fb[0] = tmp;
}

void Simulator::compute(int iterations) {
    float dx = 1.0f / width;
    float dy = 1.0f / height;
    float dt = 0.01f;
    glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
    glBindVertexArray(vertexArray);
    glViewport(0, 0, width, height);

    glUseProgram(advectProgram);
    glUniform2f(glGetUniformLocation(advectProgram, "delta"), dx, dy);
    glUniform1f(glGetUniformLocation(advectProgram, "dt"), dt);
    fb[1]->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    fb[1]->unbind();
    swapBuffers();
    
    /* Skip diffusion (looks better)
    glUseProgram(diffuseProgram);
    glUniform2f(glGetUniformLocation(diffuseProgram, "delta"), dx, dy);
    // In the Poisson-pressure equation, x represents p, b represents U2207.GIF · w, a = -(dx)2, and b = 4. [1] 
    // For the viscous diffusion equation, both x and b represent u, a = (dx)2/ndt, and b = 4 + a.
    float alpha = 0.0001 * dt * dx * dx / (width);
    glUniform1f(glGetUniformLocation(diffuseProgram, "alpha"), alpha);
    glUniform1f(glGetUniformLocation(diffuseProgram, "beta"), 4.0f + alpha);
    for (int i = 0; i < 2; i++) {
        fb[1]->bind();
        glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        fb[1]->unbind();
        swapBuffers();
    }
    */

    glUseProgram(pressureProgram);
    glUniform2f(glGetUniformLocation(pressureProgram, "delta"), dx, dy);
    // In the Poisson-pressure equation, x represents p, b represents U2207.GIF · w, a = -(dx)2, and b = 4. [1] 
    // For the viscous diffusion equation, both x and b represent u, a = (dx)2/ndt, and b = 4 + a.
    glUniform1f(glGetUniformLocation(pressureProgram, "alpha"), -dx*dx);
    glUniform1f(glGetUniformLocation(pressureProgram, "beta"), 4.0f);
    for (int i = 0; i < iterations; i++) {
        fb[1]->bind();
        glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        fb[1]->unbind();
        swapBuffers();
    }
    
    glUseProgram(projectProgram);
    glUniform2f(glGetUniformLocation(projectProgram, "delta"), dx, dy);
    fb[1]->bind();
    glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    fb[1]->unbind();
    swapBuffers();
    

    glViewport(0, 0, RESX, RESY);    
}


void Simulator::setPixel(float x, float y, void *val) {
    int tx = x * width;
    int ty = y * height;
    glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, tx, ty, 1, 1, GL_RGBA, GL_FLOAT, val);
    //glBindTexture(GL_TEXTURE_2D, fb[1]->texture);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, tx, ty, 1, 1, GL_RGBA, GL_FLOAT, val);
    //fb[0]->bind();
    //glRasterPos2i(tx, ty);
    //glDrawPixels(1, 1, GL_RGBA, GL_FLOAT, val);
    //fb[0]->unbind();
}

void Simulator::setMousePos(float x, float y) {
    glUseProgram(advectProgram);
    glUniform2f(glGetUniformLocation(advectProgram, "mousePos"), x, y);
}

void Simulator::setForceVector(float x, float y) {
    glUseProgram(advectProgram);
    glUniform2f(glGetUniformLocation(advectProgram, "forceVector"), x, y);
}