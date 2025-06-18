#include "SpriteSheet.h"
#include <iostream>

Sprite::Sprite()
{
	image = NULL;
}

Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}

void Sprite::InitSprites(int width, int height)
{
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

	image = al_load_bitmap("guy.bmp");
	if(!image) {
		std::cout << "Failed to load guy.bmp!" << std::endl;
		return;
	}
	std::cout << "Successfully loaded guy.bmp" << std::endl;
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
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
		animationDirection = 1; // second row
		break;
	case 1: // down
		y += 4;
		animationDirection = 0; // first row
		break;
	case 2: // left
		x -= 4;
		animationDirection = 2; // third row
		break;
	case 3: // right
		x += 4;
		animationDirection = 3; // fourth row
		break;
	}

	// update animation
	if(dir >= 0) {
		if(++frameCount > frameDelay) {
			frameCount = 0;
			if(++curFrame >= maxFrame)
				curFrame = 0;
		}
	}

	// collision detection
	if(collided(x, y + frameHeight)) {
		x = oldx;
		y = oldy;
	}
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationDirection * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, 
		x - xoffset, y - yoffset, 0);
}

bool Sprite::CollideSprite()
{
	return false;
}

bool Sprite::CollisionEndBlock()
{
	return endValue(x + frameWidth/2, y + frameHeight + 5);
}