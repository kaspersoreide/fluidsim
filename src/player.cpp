#include "player.h"


void Player::move() {
	
	const float movAmount = 0.087f;
	vec3 right = Rotation * vec3(1.0f, 0.0f, 0.0f);
	vec3 up = Rotation * vec3(0.0f, 1.0f, 0.0f);
	vec3 forward = Rotation * vec3(0.0f, 0.0f, 1.0f);
	forward.y = 0.0f;
	right.y = 0.0f;
	forward = normalize(forward);
	right = normalize(right);
	//vec3 dSpin(0.0f);
	//if (rot[0]) dSpin += rotAmount * forward;
	//if (rot[1]) dSpin -= rotAmount * forward;
	//if (rot[2]) dSpin += rotAmount * up;
	//if (rot[3]) dSpin -= rotAmount * up;
	//if (rot[4]) dSpin += rotAmount * right;
	//if (rot[5]) dSpin -= rotAmount * right;

	if (mov[0]) vel += movAmount * forward;
	if (mov[1]) vel -= movAmount * forward;
	if (mov[2]) vel -= movAmount * right;
	if (mov[3]) vel += movAmount * right;
	//if (mov[4]) vel += movAmount * up;
	//if (mov[5]) vel -= movAmount * up;
	vel.y -= 0.01f;
	//spin *= 0.94f;
	vel.x *= 0.7f;
	vel.z *= 0.7f;
	if (vel.y <= 0.0f && pos.y <= PLAYER_HEIGHT) {
		vel.y = 0.0f;
		pos.y = PLAYER_HEIGHT;
	}
	
	Object::move();
}

void Player::rotate(vec2 mouse) {
	const float rotAmount = 0.003f;

	Rotation = rotateY(-mouse.x * rotAmount) * rotateX(mouse.y * rotAmount);
	//vec3 right = Rotation * vec3(1.0f, 0.0f, 0.0f);
	//vec3 up = Rotation * vec3(0.0f, 1.0f, 0.0f);
	//vec3 dSpin(0.0f);
	//dSpin += rotAmount * mouse.x * up;
	//dSpin += rotAmount * mouse.y * right;
	//dSpin -= 0.92f * spin;
	
}

Player::Player() {
	pos = vec3(0.0, PLAYER_HEIGHT, 0.0);
}

Player::~Player()
{
}

void Player::jump() {
	if (pos.y <= PLAYER_HEIGHT + 0.0001f) {
		vel.y = 1.0f;
	}
}
