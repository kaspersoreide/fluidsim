#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float weight;

void main() {
    vec4 c1 = texture(tex1, uv);
    vec4 c2 = texture(tex2, uv);
    FragColor = mix(c1, c2, weight);
}