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

// A single iteration of Bob Jenkins' One-At-A-Time hashing algorithm.
uint hash(uint x) {
	x += (x << 10u);
	x ^= (x >> 6u);
	x += (x << 3u);
	x ^= (x >> 11u);
	x += (x << 15u);
	return x;
}

// Compound versions of the hashing algorithm internet person whipped together.
uint hash(uvec2 v) { return hash(v.x ^ hash(v.y)); }
uint hash(uvec3 v) { return hash(v.x ^ hash(v.y) ^ hash(v.z)); }
uint hash(uvec4 v) { return hash(v.x ^ hash(v.y) ^ hash(v.z) ^ hash(v.w)); }

// Construct a float with half-open range [0:1] using low 23 bits.
// All zeroes yields 0.0, all ones yields the next smallest representable value below 1.0.
float floatConstruct(uint m) {
	const uint ieeeMantissa = 0x007FFFFFu; // binary32 mantissa bitmask
	const uint ieeeOne = 0x3F800000u; // 1.0 in IEEE binary32

	m &= ieeeMantissa;                     // Keep only mantissa bits (fractional part)
	m |= ieeeOne;                          // Add fractional part to 1.0

	float  f = uintBitsToFloat(m);       // Range [1:2]
	return f - 1.0;                        // Range [0:1]
}

// Pseudo-random value in half-open range [0:1].
float random(float x) { return floatConstruct(hash(floatBitsToUint(x))); }
float random(vec2  v) { return floatConstruct(hash(floatBitsToUint(v))); }
float random(vec3  v) { return floatConstruct(hash(floatBitsToUint(v))); }
float random(vec4  v) { return floatConstruct(hash(floatBitsToUint(v))); }

vec2 random2(vec2 seed) {
    return 2.0 * vec2(random(seed.x), random(seed.y)) - 1.0;
}

vec2 randomVel() {
    vec2 seed = uv + center.xy;
    return 1.0 * random2(seed) * dt;
}

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
    vec2 force = 0.3 * vec2(0.0, sin(200.0 * uv.x));
    //if (distance(uv, vec2(0.05)) < 0.1) force = vec2(1.5, 0.0);
    //else if (distance(uv, vec2(0.8)) < 0.05) force = vec2(-22.5, 0.0);
    vec4 texthere = texture(tex, uv - u * dt);
    vec2 u_next = texthere.xy + force * dt  + randomVel(); //+ curlVelocity(); 
    u_next *= 0.999;
    FragColor = vec4(u_next, center.z, getCurl());
}