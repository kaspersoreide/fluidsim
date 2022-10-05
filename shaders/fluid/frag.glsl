#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;

void main() {
    vec4 vel = texture(tex, uv);
    FragColor = vec4(
        abs(vel.x - vel.y),
        abs(vel.xy),
        1.0
    );
}