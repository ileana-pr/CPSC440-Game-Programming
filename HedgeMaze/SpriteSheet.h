#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "mappy_A5.h"
#include <iostream>
using namespace std;
class Sprite
{
	friend int collided(int x, int y); // tile collision 	
	friend bool endValue( int x, int y ); // end of map collision
public:
	Sprite();
	~Sprite();
	void InitSprites(int width, int height);
	void UpdateSprites(int width, int height, int dir); //dir 1 = right, 0 = left, 2 = Standing Still
	void DrawSprites(int xoffset, int yoffset);
	bool CollideSprite();
	float getX() {return x;}
	float getY() {return y;}
	int getWidth() {return frameWidth;}
	int getHeight() {return frameHeight;}
	bool CollisionEndBlock();

private:
	float x;
	float y;
	int maxFrame;        // will be 3 (0-3 for 4 frames)
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;      
	int frameHeight;    
	int animationColumns;  // 4 columns
	int animationRows;     // 4 rows
	int animationDirection;  // 0=left, 1=right, 2=up, 3=down, 4=standing
	ALLEGRO_BITMAP *image;
	float scaleX;
	float scaleY;
};