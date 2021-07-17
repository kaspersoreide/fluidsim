#version 430

/*
    shader for creating a fluid warpmap by blending actual uv-coordinates with advected uv-coordinates
*/

in vec2 uv;

out vec4 FragColor;

uniform sampler2D vel_tex;
uniform sampler2D warp_tex;
uniform float dt;
uniform float weight;

void main() {
    vec2 u = texture(vel_tex, uv).xy;
    vec2 uv_advected = texture(warp_tex, uv - u * dt).xy;
    FragColor = vec4(mix(uv_advected, uv, weight), 0.0, 1.0);
}