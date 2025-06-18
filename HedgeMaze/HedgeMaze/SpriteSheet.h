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
	bool InitSprites(ALLEGRO_BITMAP *image);
	void UpdateSprites(int width, int height, int dir); //dir 0 = up, 1 = down, 2 = left, 3 = right
	void DrawSprites(int xoffset, int yoffset);
	void SetPosition(int newX, int newY);
	void ResetPosition();
	bool CollideSprite();
	float getX() {return x;}
	float getY() {return y;}
	int getWidth() {return frameWidth;}
	int getHeight() {return frameHeight;}
	bool CollisionEndBlock();

private:
	float x;
	float y;

	// animation
	int maxFrame;        
	int curFrame;       
	int frameCount;      
	int frameDelay;      
	int frameWidth;      
	int frameHeight;    
	int animationColumns; 
	int animationRows;    
	int animationDirection; 

	
	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *spriteSheet;
};