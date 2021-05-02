#pragma once
#include "object.h"
#define PLAYER_HEIGHT 1.8f
class Player : public Object {
public:
	void move();
	bool mov[6], rot[6];
	void jump();
	void rotate(vec2 mouse);
	Player();
	~Player();
};

