#include "SpriteSheet.h"
#include <iostream>

Sprite::Sprite()
{
	image = NULL;
	spriteSheet = NULL;
	x = 80;
	y = -10;
	maxFrame = 4;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 48;
	animationColumns = 4;
	animationDirection = 1;
	animationRows = 4;
}

Sprite::~Sprite()
{
	if (image != spriteSheet) 
		al_destroy_bitmap(image);
}

bool Sprite::InitSprites(ALLEGRO_BITMAP *image)
{
	spriteSheet = image;
	if(!spriteSheet)
		return false;
	return true;
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	// update position based on direction
	switch(dir)
	{
	case 0: // up
		y -= 4;
		animationDirection = 1;
		break;
	case 1: // down
		y += 4;
		animationDirection = 0;
		break;
	}

	// keep within screen bounds
	if (y < 0) y = 0;
	if (y + frameHeight > height) y = height - frameHeight;

	// animation
	if(dir >= 0) {
		if(++frameCount > frameDelay) {
			frameCount = 0;
			if(++curFrame >= maxFrame)
				curFrame = 0;
		}
	}

	// collision detection 
	if(collided(x, y) || collided(x, y + frameHeight) || 
	   collided(x + frameWidth, y) || collided(x + frameWidth, y + frameHeight)) {
		x = oldx;
		y = oldy;
	}
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationDirection * frameHeight;

	al_draw_bitmap_region(spriteSheet, fx, fy, frameWidth, frameHeight, 
		x - xoffset, y - yoffset, 0);
}

bool Sprite::CollisionEndBlock()
{
	
	bool centerCollision = endValue(x + frameWidth/2, y + frameHeight/2);
	return centerCollision;
}

void Sprite::SetPosition(int newX, int newY)
{
	x = newX;
	y = newY;
}