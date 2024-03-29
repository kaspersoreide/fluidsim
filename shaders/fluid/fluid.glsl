#version 430

/** Fluid simulation, based on http://developer.download.nvidia.com/books/HTML/gpugems/gpugems_ch38.html
 *  
 *  each pixel stores pressure and velocity, so whole texture is a vector field
 *  pixel's x and y values are velocity, and z is pressure
 *  This shader computes new velocity by advecting and diffusing velocity
 *  The result is not divergence free and must be fixed in another shader
 */

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

float dt = 0.01;
float viscosity = 0.000019;

vec2 getGradient() {
    //gradient of pressure
    return vec2 (
        (right.z - left.z) / (2 * delta.x),
        (up.z - down.z) / (2 * delta.y)
    );
}

float getDivergence() {
    float dudx = (right.x - left.x) / (2 * delta.x);
    float dvdy = (up.y - down.y) / (2 * delta.y);
    return dudx + dvdy;
}

float getLaplacian(int idx) {
    return (
        (left[idx] - 2 * center[idx] + right[idx]) / (delta.x*delta.x)
        + (up[idx] - 2 * center[idx] + down[idx]) / (delta.y*delta.y)
    );
}

vec4 advect() {
    vec2 u = center.xy;
    return texture(tex, uv - u * dt);
}

vec2 diffuseVelocity() {
    vec2 del2 = vec2(getLaplacian(0), getLaplacian(1));
    return viscosity * dt * del2;
}

float diffuseDye() {
    return viscosity * dt * getLaplacian(3);
}

float getCurl() {
    return (up.x - down.x) / (2 * delta.x) - (left.y - right.y) / (2 * delta.y);
}

vec2 curlVelocity() {
    vec2 grad = getGradient();
    return delta.x * dt * center.z * vec2(grad.y, -grad.x);
}

void main() {
    vec2 force = vec2(0.0);
    if (distance(uv, vec2(0.5, 0.5)) < 0.1) force = vec2(1.5, 1.5);
    vec4 advected = advect();
    vec2 w = advected.xy;
    w += diffuseVelocity();
    w += force * dt;
    w += curlVelocity();

    FragColor = vec4(w, getCurl(), advected.w);
}