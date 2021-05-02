#version 430

in vec2 screenPos;

out vec4 FragColor;

uniform uvec2 res;
uniform float ratio;
//uniform vec4 spheres[32];
uniform mat4 cam;
uniform float time;

float spacing = 8.0;

vec4 sphere = vec4(vec3(spacing / 2.0), 1.0);

float opSmoothUnion( float d1, float d2, float k ) {
    float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) - k*h*(1.0-h); 
}

vec3 vecToSphere(vec3 p) {
	return sphere.xyz - mod(p, spacing);
}

float distToCube(vec3 p) {
	vec3 relpos = vecToSphere(p);
	float x = max(0.0, abs(relpos.x) - 1.0);
	float y = max(0.0, abs(relpos.y) - 1.0);
	float z = max(0.0, abs(relpos.z) - 1.0);
	return sqrt(x*x + y*y + z*z);
}

float distSphere(vec3 p) {
	return length(vecToSphere(p)) - sphere.w;
}

float distFunky(vec3 p) {
	//vec3 d = vecToSphere(p);
	float k = 3.0 * sin(time + p.z); // or some other amount
	p = mod(p + 4.0, 8.0) - 4.0;
    float c = cos(k*p.y);
    float s = sin(k*p.y);
    mat2  m = mat2(c,-s,s,c);
    p = vec3(m*p.xz,p.y);
	//p = abs(p);
  	//return (p.x+p.y+p.z-2.0)*0.57735027;
	float x = max(0.0, abs(p.x) - 1.0);
	float y = max(0.0, abs(p.y) - 1.0);
	float z = max(0.0, abs(p.z) - 1.0);
	return sqrt(x*x + y*y + z*z);
}

vec2 mandelBulb(vec3 pos) {
	vec3 z = vec3(pos.x, pos.y-2.0, pos.z);
	float dr = 1.0;
	float r = 0.0;
	float Power = 8.0;
	int steps = 0;
	for (int i = 0; i < 10; i++) {
		r = length(z);
		if (r > 4.0) break;

		// convert to polar coordinates
		float theta = acos(z.z / r);
		float phi = atan(z.y, z.x);
		dr = pow(r, Power - 1.0)*Power*dr + 1.0;

		// scale and rotate the point
		float zr = pow(r, Power);
		theta = theta * Power;
		phi = phi * Power;

		// convert back to cartesian coordinates
		z = zr * vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
		z += pos;
		steps++;
	}
	return vec2(0.5*log(r)*r / dr, steps);
}

float distGround(vec3 pos, vec3 cPos) {
	vec2 diff = pos.xz - cPos.xz;
	return pos.y;
}

void main() {
	//c goes from -1 to 1 in x and y directions
	vec2 c = vec2(
		screenPos.x * ratio,
		screenPos.y
	);

	vec3 cPos = cam[3].xyz;

	//this does the projection outwards. +z is forward
	vec3 dir = (cam * vec4(normalize(vec3(0.9 * c, 1.0)), 0.0)).xyz;

	int raysteps = 0;
	vec3 raypos = cPos;
	float dist = 1.0;
	vec2 mandelinfo;
	float gravConstant = -0.001;
	while (dist > 0.0001 && raysteps < 50) {
		if (dir.y < 0.0 && raypos.y < 0.0) {
			dir.y *= -1;
			raysteps = 30;
			raypos.y *= -1.0;
		} 
		dist = distToCube(raypos);
		//dir += gravConstant * vecToSphere(raypos) / (dist*dist);
		//dir = normalize(dir);
		raypos += dist * dir;
		raysteps += 1;
	}
	vec3 normal = vecToSphere(raypos);
	//vec3 lightdir = normalize(vec3(1.0, 1.0, 1.0));
	//float reflection = clamp(dot(normal, lightdir), 0.2, 1.0);
	float shade = exp(-0.01 * distance(raypos, cPos));
	FragColor = shade * vec4(
		0.5 + 0.5 * cos(time + 0.1 * float(raysteps)),
		0.5 + 0.5 * sin(time + 0.1 * float(raysteps)),
		0.5 + 0.5 * cos(0.452 * time + 0.3 * float(raysteps)),
		1.0
	);
}