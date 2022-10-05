#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;
uniform float dt;
uniform vec2 forcePos;
//distance between pixels in uv space
uniform vec2 delta;
uniform vec2 mousePos;
uniform vec2 forceVector;

vec4 up = texture(tex, vec2(uv.x, uv.y + delta.y));
vec4 down = texture(tex, vec2(uv.x, uv.y - delta.y));
vec4 left = texture(tex, vec2(uv.x - delta.x, uv.y));
vec4 right = texture(tex, vec2(uv.x + delta.x, uv.y));
vec4 center = texture(tex, uv);


float getCurl() {
    return (up.x - down.x) / (2 * delta.x) - (left.y - right.y) / (2 * delta.y);
}

vec2 swirl() {
    float swirlFactor = 6.0; //WARNING: high value causes instability
    return swirlFactor * dt * vec2(up.x - down.x, left.y - right.y);
}


void main() {
    vec2 u = center.xy;
    vec2 force = forceVector * exp(-50.0 * distance(uv, mousePos));
    vec4 texthere = texture(tex, uv - u * dt);
    vec2 u_next = texthere.xy + force * dt - swirl(); 
    FragColor = vec4(u_next, center.z, getCurl());
}