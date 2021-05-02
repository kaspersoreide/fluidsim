#version 430

/** step 2 in Fluid simulation, based on http://developer.download.nvidia.com/books/HTML/gpugems/gpugems_ch38.html
 *  
 *  each pixel stores pressure and velocity, so whole texture is a vector field
 *  pixel's x and y values are velocity, and z is pressure
 *  This shader solves diffusion and has to be run many iterations
 */

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
    vec2 u_next = (up.xy + down.xy + left.xy + right.xy + alpha * center.xy) / beta;
    FragColor = vec4(u_next, center.zw);
}