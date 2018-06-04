
#include "player.h"
Player::Player(Sprite sprite, int pos_x, int pos_y, int w, int h, Color color, int mode) {
	this->sprite = sprite;
	this->color = color;
	this->sprite.setTextureRect(IntRect(pos_x*16, pos_y*16, w, h));
	this->w = w-2;
	this->h = h-2;
	this->mode = mode;
	dir = UP;
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	speed = 0;
	CurrentFrame = 0;
	bullet = 0;
	old_time = 0;
	boom_kadr = 0;
	animeboom = false;
	
	
}
Player::Player() {
	w = 0; h = 0; dir = 0; x = 0; y = 0; dx = 0; dy = 0; speed = 0; CurrentFrame = 0;
}
Player::~Player() {

}
void Player::setscale(float scale)
{
	sprite.setScale(scale, scale);
	w *= scale;
	h *= scale;
}
void Player::update(float time, Clock &bullet_timer, RenderWindow& window, Sprite tile_map) {

	this->sprite.setColor(color);
	dx = 0, dy = 0;
	if (bullet != nullptr) {
		window.draw(bullet->sprite);
		if (bullet->update(time))
			bullet = 0;
		if (bullet != nullptr)
			if (bullet->interactionWithMap(tile_map, window, time, this)) {
				bullet = 0;
			}
		
	}

	if (animeboom) {
		boom_kadr += 0.09;
		if (boom_kadr > 4) {
			animeboom = false;
			boom_kadr = 0;
		}
		tile_map.setPosition(animeboom_x, animeboom_y);
		tile_map.setTextureRect(IntRect(16 * 16 + 16 * (int)boom_kadr, 6 * 16, 16, 16));
		window.draw(tile_map);
	}
	float cspeed = 0.1;
	switch (mode) {
	case 1:
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			dir = 1;
			speed = cspeed;
			CurrentFrame += 0.006*time;
			if (CurrentFrame > 2)
				CurrentFrame = 0;
			sprite.setTextureRect(IntRect(14 * 16 + 16 * (int)CurrentFrame, 0, 16, 16));
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			dir = 0;
			speed = cspeed;
			CurrentFrame += 0.006*time;
			if (CurrentFrame > 2)
				CurrentFrame = 0;

			sprite.setTextureRect(IntRect(10 * 16 + 16 * (int)CurrentFrame, 0, 16, 16));
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			dir = 2;
			speed = cspeed;
			CurrentFrame += 0.006*time;
			if (CurrentFrame > 2)
				CurrentFrame = 0;

			sprite.setTextureRect(IntRect(8 * 16 + 16 * (int)CurrentFrame, 0, 16, 16));
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			dir = 3;
			speed = cspeed;
			CurrentFrame += 0.006*time;
			if (CurrentFrame > 2)
				CurrentFrame = 0;

			sprite.setTextureRect(IntRect(12 * 16 + 16 * (int)CurrentFrame, 0, 16, 16));
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			float new_time = bullet_timer.getElapsedTime().asSeconds();

			if (new_time - old_time > 1 && !bullet) {
				old_time = new_time;

				bullet = new Bullet(sprite, 0.3, dir, x + 55 / 2, y + 55 / 2);
				bullet->setScale(4);

			}
		}
		break;
	case 2:
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			dir = 1;
			speed = cspeed;
			CurrentFrame += 0.006*time;
			if (CurrentFrame > 2)
				CurrentFrame = 0;
			sprite.setTextureRect(IntRect(14 * 16 + 16 * (int)CurrentFrame, 0, 16, 16));
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			dir = 0;
			speed = cspeed;
			CurrentFrame += 0.006*time;
			if (CurrentFrame > 2)
				CurrentFrame = 0;

			sprite.setTextureRect(IntRect(10 * 16 + 16 * (int)CurrentFrame, 0, 16, 16));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			dir = 2;
			speed = cspeed;
			CurrentFrame += 0.006*time;
			if (CurrentFrame > 2)
				CurrentFrame = 0;

			sprite.setTextureRect(IntRect(8 * 16 + 16 * (int)CurrentFrame, 0, 16, 16));
		}
		if (Keyboard::isKeyPressed(Keyboard::RShift)) {
			dir = 2;
			speed = cspeed;
			CurrentFrame += 0.006*time;
			if (CurrentFrame > 2)
				CurrentFrame = 0;

			sprite.setTextureRect(IntRect(8 * 16 + 16 * (int)CurrentFrame, 0, 16, 16));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			dir = 3;
			speed = cspeed;
			CurrentFrame += 0.006*time;
			if (CurrentFrame > 2)
				CurrentFrame = 0;

			sprite.setTextureRect(IntRect(12 * 16 + 16 * (int)CurrentFrame, 0, 16, 16));
		}
		if (Keyboard::isKeyPressed(Keyboard::Insert)) {
			float new_time = bullet_timer.getElapsedTime().asSeconds();

			if (new_time - old_time > 1 && !bullet) {
				old_time = new_time;

				bullet = new Bullet(sprite, 0.3, dir, x + 55 / 2, y + 55 / 2);
				bullet->setScale(4);

			}
		}
		break;
	}
	
	switch (dir) {
	case LEFT:
		dx = -speed;
		dy = 0;
		break;
	case RIGHT:
		dx = speed;
		dy = 0;
		break;
	case UP:
		dy = -speed;
		dx = 0;
		break;
	case DOWN:
		dy = speed;
		dx = 0;
		break;
	}
	x += dx*time;
	y += dy*time;
	speed = 0;
	
	sprite.setPosition(x, y);
	check_where_i_am();
	
	window.draw(sprite);
	interactionWithMap(tile_map, window);
}
void Player::move(float x, float y) {
	sprite.move(x, y);
}

float Player::getX()
{
	return x;
}

float Player::getY()
{
	return y;
}
void Player::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	sprite.setPosition(x, y);
}
void Player::check_where_i_am() {
	if (x < -8)
		x = -8;
	if (x > 1024+64 - 56)
		x = 1024+64 - 56;

	if (y < -8)
		y = -8;
	if (y > 640 - 56)
		y = 640 - 56;
}

