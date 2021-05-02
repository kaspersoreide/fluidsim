#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;
//distance between pixels in uv space
uniform vec2 delta;

vec4 up = texture(tex, vec2(uv.x, uv.y + delta.y));
vec4 down = texture(tex, vec2(uv.x, uv.y - delta.y));
vec4 left = texture(tex, vec2(uv.x - delta.x, uv.y));
vec4 right = texture(tex, vec2(uv.x + delta.x, uv.y));
vec4 center = texture(tex, uv);

void main() {
    vec2 grad = vec2 (
        (right.z - left.z) / (2 * delta.x),
        (up.z - down.z) / (2 * delta.y)
    );
    FragColor = vec4(center.xy - grad, center.zw);
}