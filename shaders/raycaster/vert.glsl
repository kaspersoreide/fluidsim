#version 430

layout(location = 0) in vec4 pos;

out vec2 screenPos;

void main() {
	screenPos = pos.xy;
	gl_Position = pos;
}