#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "mappy_A5.h"
#include <iostream>
using namespace std;



class Sprite
{
	friend int collided(int x, int y);
	friend bool endValue(int x, int y);
public:
	Sprite();
	~Sprite();
	bool InitSprites(ALLEGRO_BITMAP *image);
	void UpdateSprites(int width, int height, int dir);
	void DrawSprites(int xoffset, int yoffset);
	void SetPosition(int newX, int newY);
	bool CollisionEndBlock();
	float getX() {return x;}
	float getY() {return y;}
	int getWidth() {return frameWidth * 1.4;}
	int getHeight() {return frameHeight * 1.4;}
	void SetSpriteParameters(int width, int height, int frames, int rows, int startRow, int startCol);

private:
	float x;
	float y;

	int maxFrame;        
	int curFrame;       
	int frameCount;      
	int frameDelay;      
	int frameWidth;      
	int frameHeight;    
	int animationColumns; 
	int animationRows;    
	int animationDirection;
	int startRow;        
	int startCol;       

	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *spriteSheet;
};