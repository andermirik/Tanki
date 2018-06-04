#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"
#include<iostream>
#include<cmath>
#include<conio.h>
using namespace sf;
using namespace std;

float water_frame = 0;


int main()
{
	RenderWindow window(VideoMode(1024 + 64, 640), "Its alive!!");//,Style::Fullscreen);

	Image tilemap;
	tilemap.loadFromFile("images/tilemap.png");
	tilemap.createMaskFromColor(Color(0, 0, 1));
	tilemap.createMaskFromColor(Color(0, 0, 0));
	Texture texture_tilemap;
	texture_tilemap.loadFromImage(tilemap);
	Sprite player_sprite;
	player_sprite.setTexture(texture_tilemap);

	Player *player = new Player(player_sprite, 8, 0, 16, 16, Color(255, 0, 0), 1);
	Player * player2 = new Player(player_sprite, 8, 0, 16, 16, Color(0, 255, 0), 2);
	player->setPosition(7 * 64, 1 * 64);
	player2->setPosition(64, 64);
	
	player2->setscale(4);	
	player->setscale(4);
	Sprite tile_map;
	tile_map.setScale(4, 4);
	tile_map.setTexture(texture_tilemap);
	Clock clock;




	Clock bullet_timer;


	while (window.isOpen())
	{
		float time = (float)clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//cout << player->getX() << ";" << player->getY() << endl;




		window.clear(Color(128, 106, 89));

		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				tile_map.setPosition(j * 64, i * 64);
				switch (TileMap[i][j])
				{
				case 'K':
					tile_map.setTextureRect(IntRect(17 * 16, 2 * 16, 16, 16));
					window.draw(tile_map);
					break;
				case 'B':
					tile_map.setTextureRect(IntRect(16 * 16, 0, 16, 16));
					window.draw(tile_map);
					break;
				case 'W':
					water_frame += 0.00015*time;
					if (water_frame > 2)
						water_frame = 0;
					tile_map.setTextureRect(IntRect(16 * 16 + 16 * (int)water_frame, 3 * 16, 16, 16));
					window.draw(tile_map);
					break;
				case 'U':
					tile_map.setTextureRect(IntRect(16 * 16, 16, 16, 16));
					window.draw(tile_map);
					break;
				}
			}
		}

		if (_kbhit()) {
			char k = _getch();
			cout << k <<endl;
			if (k == 'r') {
				if (player2 == nullptr) {
					player2 = new Player(player_sprite, 8, 0, 16, 16, Color(0, 255, 0), 2);
					player2->setscale(4);
					player2->setPosition(64, 64);
				}
				if (player == nullptr) {
					player = new Player(player_sprite, 8, 0, 16, 16, Color(255, 0, 0), 1);
					player->setscale(4);
					player->setPosition(7 * 64, 64);
				}
					
			}

		}
		if (player2 != nullptr && player != nullptr) {
			if(player->bullet != nullptr)
				if (player->bullet->checkPlayer(player2, player)) {
					player2 = nullptr;
					player->bullet = nullptr;
				}
		}


		if (player != nullptr && player2!= nullptr) {
			if(player2->bullet != nullptr)
				if (player2->bullet->checkPlayer(player, player2)) {
					player = nullptr;
					player2->bullet = nullptr;
				}
		}

		if (player2 != nullptr)
			player2->update(time, bullet_timer, window, tile_map);
		
		if (player != nullptr) 
			player->update(time, bullet_timer, window, tile_map);
		
		window.display();
	}
	return 0;
}


bool Bullet::interactionWithMap(Sprite &tile_map, RenderWindow &window, float time, Player * player) {

	for (int i = y / 64; i < (y + h) / 64; i++) {
		for (int j = x / 64; j < (x + w) / 64; j++) {
			switch (TileMap[i][j]) {
			case 'B':
				TileMap[i][j] = ' ';
				delete this;
				
				player->animeboom = true;
				player->animeboom_y = i*64;
				player->animeboom_x = j*64;
				
				return true;
				break;
			case 'U':
				delete this;

				return true;
				break;
			case 'K':
				tile_map.setPosition(j * 64, i * 64);
				tile_map.setTextureRect(IntRect(17 * 16, 2 * 16, 16, 16));

				window.draw(tile_map);
				
			}
		}
	}
	return false;
}


void Player::interactionWithMap(Sprite &tile_map, RenderWindow &window) {
	for (int i = y / 64; i < (y + h) / 64; i++) {
		for (int j = x / 64; j < (x + w) / 64; j++) {
			switch (TileMap[i][j]) {
			case 'B': case 'U': case 'W':
				if (dy > 0)
					y = i * 64 - h - 2;
				if (dy < 0)
					y = i * 64 + 64;
				if (dx > 0)
					x = j * 64 - 59;
				if (dx < 0)
					x = j * 64 + w + 8;
				break;
			case 'K':
				tile_map.setPosition(j * 64, i * 64);
				tile_map.setTextureRect(IntRect(17 * 16, 2 * 16, 16, 16));

				window.draw(tile_map);
				
				break;
			}
		}
	}

}

bool Bullet::checkPlayer(Player* target, Player* owner) {
	
	if ((x > target->x && x < target->x + target->w - w) && (y<target->y + target->h - h && y > target->y))
	{
		owner->animeboom_x = target->x;
		owner->animeboom_y = target->y;
		owner->animeboom = true;
		delete target;
		delete this;
		return true;
	}
	return false;
}
