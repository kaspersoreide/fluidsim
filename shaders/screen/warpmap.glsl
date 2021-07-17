#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D warpmap;
uniform sampler2D img;

void main() {
    vec2 warped_uv = texture(warpmap, uv).xy;
    FragColor = texture(img, warped_uv);
}