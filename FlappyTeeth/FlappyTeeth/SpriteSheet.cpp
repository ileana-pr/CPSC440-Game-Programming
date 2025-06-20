#include "SpriteSheet.h"
#include <iostream>

Sprite::Sprite()
{
	image = NULL;
	spriteSheet = NULL;
	x = 80;
	y = -10;
	maxFrame = 3;       
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;    
	frameHeight = 32;
	animationColumns = 3; 
	animationDirection = 0;
	animationRows = 1;   
	startRow = 11;       
	startCol = 3;       
}

Sprite::~Sprite()
{
	if (image != spriteSheet) 
		al_destroy_bitmap(image);
}

bool Sprite::InitSprites(ALLEGRO_BITMAP *image)
{
	if(image == NULL)
		return false;
	spriteSheet = image;
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
		break;
	case 1: // down
		y += 4;
		break;
	}

	// keep within screen bounds
	if (y < 0) y = 0;
	if (y + frameHeight > height) y = height - frameHeight;

	// update animation
	if(++frameCount > frameDelay) {
		frameCount = 0;
		curFrame = (curFrame + 1) % maxFrame;  
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
	// position in sprite sheet
	int fx = (startCol + curFrame) * frameWidth;  
	int fy = startRow * frameHeight;  

	// draw scaled up by 40%
	ALLEGRO_BITMAP* temp = al_create_bitmap(frameWidth, frameHeight);
	al_set_target_bitmap(temp);
	al_draw_bitmap_region(spriteSheet, fx, fy, frameWidth, frameHeight, 0, 0, 0);
	al_set_target_backbuffer(al_get_current_display());
	al_draw_scaled_bitmap(temp, 
		0, 0, frameWidth, frameHeight,
		x - xoffset, y - yoffset, 
		frameWidth * 1.4, frameHeight * 1.4, 
		0);
	al_destroy_bitmap(temp);
}

// Draw sprites with rotation and scaling
void Sprite::DrawSpritesWithTransform(int xoffset, int yoffset, float rotation, float scale)
{
	int fx = (startCol + curFrame) * frameWidth;  
	int fy = startRow * frameHeight;  

	ALLEGRO_BITMAP* temp = al_create_bitmap(frameWidth, frameHeight);
	al_set_target_bitmap(temp);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));  
	al_draw_bitmap_region(spriteSheet, fx, fy, frameWidth, frameHeight, 0, 0, 0);
	al_set_target_backbuffer(al_get_current_display());
	
	float scaledWidth = frameWidth * 1.4f * scale;
	float scaledHeight = frameHeight * 1.4f * scale;
	float centerX = x - xoffset + scaledWidth / 2;
	float centerY = y - yoffset + scaledHeight / 2;
	
	al_draw_scaled_rotated_bitmap(temp,
		frameWidth/2, frameHeight/2,  
		centerX, centerY,  
		scale * 1.4f, scale * 1.4f, 
		rotation,  
		0);  
	
	al_destroy_bitmap(temp);
}

// Check if sprite collides with any block
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

void Sprite::SetSpriteParameters(int width, int height, int frames, int rows, int sRow, int sCol)
{
	frameWidth = width;
	frameHeight = height;
	maxFrame = frames;
	animationRows = rows;
	animationColumns = frames;
	startRow = sRow;
	startCol = sCol;
	curFrame = 0;
}