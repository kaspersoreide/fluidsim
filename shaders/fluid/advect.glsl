#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;
uniform float dt;
uniform vec2 forcePos;
//distance between pixels in uv space
uniform vec2 delta;

vec4 up = texture(tex, vec2(uv.x, uv.y + delta.y));
vec4 down = texture(tex, vec2(uv.x, uv.y - delta.y));
vec4 left = texture(tex, vec2(uv.x - delta.x, uv.y));
vec4 right = texture(tex, vec2(uv.x + delta.x, uv.y));
vec4 center = texture(tex, uv);


vec2 getGradient() {
    //gradient of curl
    return vec2 (
        (right.w - left.w) / (2 * delta.x),
        (up.w - down.w) / (2 * delta.y)
    );
}

float getCurl() {
    return (up.x - down.x) / (2 * delta.x) - (left.y - right.y) / (2 * delta.y);
}

vec2 curlVelocity() {
    vec2 grad = getGradient();
    return 0.001 * delta.x * dt * center.w * vec2(grad.y, -grad.x);
}


void main() {
    vec2 u = center.xy;
    vec2 force = vec2(0.0);
    if (distance(uv, vec2(0.2)) < 0.05) force = vec2(1.5, 0.0);
    //else if (distance(uv, vec2(0.8)) < 0.05) force = vec2(-22.5, 0.0);
    vec4 texthere = texture(tex, uv - u * dt);
    vec2 u_next = texthere.xy + force * dt; //+ curlVelocity(); 
    FragColor = vec4(u_next, center.z, getCurl());
}