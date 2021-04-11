#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;

void main() {

    float pi = 3.1415926;
    vec4 c = texture(tex, uv);
    /*
    float a = atan(c.x, c.y);
    FragColor = vec4(
        0.5 * sin(a) + 0.5, 
        0.5 * sin(a + pi / 3),
        0.5 * sin(a + 2.0 * pi / 3),
        1.0
    );
    */

    FragColor = vec4(c.x*c.x + c.y*c.y);
}