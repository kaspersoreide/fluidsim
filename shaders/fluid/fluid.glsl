#version 430

/** Fluid simulation, based on http://developer.download.nvidia.com/books/HTML/gpugems/gpugems_ch38.html
 *  
 *  each pixel stores pressure and velocity, so whole texture is a vector field
 *  pixel's x and y values are velocity, and z is pressure
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

float getLaplacian() {
    return (
        (left.z - 2 * center.z + right.z) / (delta.x*delta.x)
        + (up.z - 2 * center.z + down.z) / (delta.y*delta.y)
    );
}

void main() {
    float viscosity = 0.03;
    float density = 0.1;
    vec2 force(0.0);
    if (distance(uv, vec2(0.5, 0.5)) < delta.x) force = vec2(0.1, 0.0);
    

    float dt = 0.01;
    float div = getDivergence();

}