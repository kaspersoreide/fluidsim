#include <GL/glew.h>
#include <glm/glm.hpp>

class Raycaster {
public:
    Raycaster();
    void render(glm::mat4 cam);
    void setResolution(unsigned int x, unsigned int y);
    void setTime(float t);
private:
    GLuint vertexArray, program;
};