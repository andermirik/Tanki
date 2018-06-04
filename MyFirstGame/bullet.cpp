#include "player.h"
Bullet::Bullet(Sprite sprite, float speed, int dir, float x, float y) {
	this->sprite = sprite;
	this->speed = speed;
	this->dir = dir;

	this->x = x;
	this->y = y;

	if (dir > 3)
		dir = 3;
	switch (dir)
	{
	case LEFT:
		w = 4;
		h = 3;
		dx = -speed;
		dy = 0;
		this->sprite.setTextureRect(IntRect(330, 102, w, h));
		break;
	case RIGHT:
		w = 4;
		h = 3;
		dx = speed;
		dy = 0;
		this->sprite.setTextureRect(IntRect(346, 102, w, h));
		break;
	case UP:
		w = 3;
		h = 4;
		dy = -speed;
		dx = 0;
		this->sprite.setTextureRect(IntRect(323, 102, w, h));
		break;
	case DOWN:
		w = 3;
		h = 4;
		dy = speed;
		dx = 0;
		this->sprite.setTextureRect(IntRect(339, 102, w, h));
		break;
	}

	this->sprite.setPosition(x, y);
	
}
Bullet::~Bullet() {

}
void Bullet::setScale(float scale) {
	sprite.setScale(scale, scale);
	this->scale = scale;
}

bool Bullet::update(float time) {
	x += dx*time;
	y += dy*time;
	sprite.setPosition(x, y);
	if (x < -8) {
		delete this;
		return true;
	}
	if (x > 1024 + 64+60)
	{
		delete this;
		return true;
	}

	if (y < -8) {
		delete this;
		return true;
	}
	if (y > 640 + 56)
	{
		delete this;
		return true;
	}
	return false;
}

