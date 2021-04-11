#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;

void main() {
    vec4 c = texture(tex, uv);
    FragColor = c;
}