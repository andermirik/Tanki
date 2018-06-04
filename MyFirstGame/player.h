#include <SFML/Graphics.hpp>


class Bullet;
using namespace sf;
class Player {
private:
	
	enum dirrection { LEFT, RIGHT, UP, DOWN };
	float CurrentFrame;
	Color color;
	
	float old_time;
	int mode;
	
public:
	Player(Sprite sprite, int pos_x, int pos_y, int w, int h, Color color, int mode);
	Sprite sprite;
	Bullet* bullet;
	float x, y, w, h;
	Player();
	~Player();
	float boom_kadr;
	bool animeboom;

	float animeboom_x;
	float animeboom_y;
	float speed;
	int dir;
	float dx, dy;
	void setscale(float);
	void update(float, Clock&, RenderWindow& window, Sprite tile_map);
	void move(float x, float y);
	float getX();
	float getY();
	void setPosition(float, float);
	void check_where_i_am();
	void interactionWithMap(Sprite&, RenderWindow&);
};

class Bullet {
public:
	Sprite sprite;
	float dx, dy;
	float x, y, w, h;
	float dir;
	float speed;
	bool update(float);
	void setScale(float);
	Bullet(Sprite sprite, float speed, int dir, float x, float y);
	~Bullet();
	bool interactionWithMap(Sprite &tile_map, RenderWindow &window, float time, Player * player);
	bool checkPlayer(Player * target, Player * owner);
private:
	enum dirrection { LEFT, RIGHT, UP, DOWN };

	float scale;
};