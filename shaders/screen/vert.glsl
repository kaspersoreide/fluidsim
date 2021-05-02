#version 430

layout(location = 0) in vec4 pos;

out vec2 uv;

void main() {
    uv = 0.5 * pos.xy + 0.5;
	gl_Position = pos;
}