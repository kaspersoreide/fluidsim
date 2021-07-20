#include "simulator.h"
#include <algorithm>

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

    for (int i = 0; i < 2; i++) {
        fb[i] = new Framebuffer(width, height, GL_RGBA32F, GL_REPEAT, GL_LINEAR, GL_FLOAT, GL_RGBA);
        warp_fb[i] = new Framebuffer(width, height, GL_RG16F, GL_REPEAT, GL_LINEAR, GL_FLOAT, GL_RG);
    } 

    renderProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/frag.glsl");
    advectProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/advect.glsl");
    diffuseProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/diffuse.glsl");
    pressureProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/solvepressure.glsl");
    projectProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/project.glsl");
    advectorProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/advector.glsl");
    warpProgram = loadShaders("shaders/fluid/vert.glsl", "shaders/fluid/warpmap.glsl");
}

void Simulator::render() {
    glUseProgram(renderProgram);
    glBindVertexArray(vertexArray);
    glBindTexture(GL_TEXTURE_2D, fb[1]->texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Simulator::compute(int iterations, float warp_amount) {
    glActiveTexture(GL_TEXTURE0);
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
    std::swap(fb[0], fb[1]);
    /*
    glUseProgram(diffuseProgram);
    glUniform2f(glGetUniformLocation(diffuseProgram, "delta"), dx, dy);
    // In the Poisson-pressure equation, x represents p, b represents U2207.GIF · w, a = -(dx)2, and b = 4. [1] 
    // For the viscous diffusion equation, both x and b represent u, a = (dx)2/ndt, and b = 4 + a.
    float alpha = 0.0001 * dt * dx * dx / (width);
    glUniform1f(glGetUniformLocation(diffuseProgram, "alpha"), alpha);
    glUniform1f(glGetUniformLocation(diffuseProgram, "beta"), 4.0f + alpha);
    for (int i = 0; i < 20; i++) {
        fb[1]->bind();
        glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        fb[1]->unbind();
        swapBuffers();
    }*/

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
        std::swap(fb[0], fb[1]);
    }
    
    glUseProgram(projectProgram);
    glUniform2f(glGetUniformLocation(projectProgram, "delta"), dx, dy);
    fb[1]->bind();
    glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    fb[1]->unbind();
    std::swap(fb[0], fb[1]);
    //warp warpmap
    glUseProgram(warpProgram);
    glUniform1f(glGetUniformLocation(warpProgram, "dt"), dt);
    glUniform1f(glGetUniformLocation(warpProgram, "weight"), warp_amount);
    warp_fb[1]->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
    glUniform1i(glGetUniformLocation(warpProgram, "vel_tex"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, warp_fb[0]->texture);
    glUniform1i(glGetUniformLocation(warpProgram, "warp_tex"), 1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    warp_fb[1]->unbind();
    std::swap(warp_fb[0], warp_fb[1]);


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

void Simulator::advect(Framebuffer* back, Framebuffer* front) {
    //this function uses the simulator's velocity field to move the entire image in target
    //binds the texture in target and then blits result into it
    //this needs to be done because rendering a texture to itself produces undefined behaviour
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fb[0]->texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, back->texture);
    front->bind();
    glViewport(0, 0, front->width, front->height);
    glUseProgram(advectorProgram);
    float dt = 0.01f;
    glUniform1f(glGetUniformLocation(advectorProgram, "dt"), dt);
    glBindVertexArray(vertexArray);
    glUniform1i(glGetUniformLocation(advectorProgram, "vel_tex"), 0);
    glUniform1i(glGetUniformLocation(advectorProgram, "img_tex"), 1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    front->unbind();
    glViewport(0, 0, RESX, RESY);
    glActiveTexture(GL_TEXTURE0);
}
