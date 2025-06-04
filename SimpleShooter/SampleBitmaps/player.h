#ifndef PLAYERH
#define PLAYERH
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "BadGuy.h"

class player
{
public:
	player(int HEIGHT);
	~player();
	void DrawPlayer();
	void MoveUp(BadGuy BadGuys[], int cSize);
	void MoveDown(int HEIGHT, BadGuy BadGuys[], int cSize);
	void MoveLeft(BadGuy BadGuys[], int cSize);
	void MoveRight(int WIDTH, BadGuy BadGuys[], int cSize);
	bool playerCollision(int new_x, int new_y, BadGuy BadGuys[], int cSize);
	int getBoundX(){return boundx;}
	int getBoundY(){return boundy;}
	int getX(){return x;}
	int getY(){return y;}
private:
	int x;
	int y;
	int speed;
	int dir;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP *image;
};
#endif

