#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;
//distance between pixels in uv space
uniform vec2 delta;
uniform float alpha;
uniform float beta;

vec4 up = texture(tex, vec2(uv.x, uv.y + delta.y));
vec4 down = texture(tex, vec2(uv.x, uv.y - delta.y));
vec4 left = texture(tex, vec2(uv.x - delta.x, uv.y));
vec4 right = texture(tex, vec2(uv.x + delta.x, uv.y));
vec4 center = texture(tex, uv);

void main() {
    float div = (right.x - left.x) / (2 * delta.x) + (up.y - down.y) / (2 * delta.y);
    float p_next = (up.z + down.z + left.z + right.z + alpha * div) / beta;
    FragColor = vec4(center.xy, p_next, center.w);
}