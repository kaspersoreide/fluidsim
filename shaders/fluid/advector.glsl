#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D vel_tex;
uniform sampler2D img_tex;
uniform float dt;

void main() {
    vec2 u = texture(vel_tex, uv).xy;
    FragColor = texture(img_tex, uv - u * dt);
}