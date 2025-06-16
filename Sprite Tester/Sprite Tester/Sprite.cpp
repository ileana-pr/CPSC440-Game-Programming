#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "Sprite.h"
#include <iostream>
using namespace std;

sprite::sprite()
{
	for (int i = 0; i < 9; i++) image[i] = nullptr;
	x = rand() % 500 + 50;  
	y = rand() % 300 + 50;  
	xspeed = (rand() % 2) ? 3 : -3; 
	yspeed = (rand() % 2) ? 3 : -3;  
	xdelay = 1;
	ydelay = 1;
	xcount = ycount = 0;
	curframe = 0;
	framecount = 0;
	framedelay = 8;
	collisionIsTrue = false;
	scale = 1.0;
	rotation_angle = 0.0;
	currentColor = al_map_rgb(255, 255, 255);  
	collisionTime = 0;
	scaredLifetime = 0;
	spinningLifetime = 0;
	
	// set all powers to false
	for(int i = 0; i < 4; i++) specialtyPower[i] = false;
	
	// load sprite and set flag if successful 
	live = load_animated_sprite(8);
}

void sprite::drawSprite()
{
	if(specialtyPower[0])  // spinning sprite
	{
		ALLEGRO_BITMAP* current = image[curframe];
		int cx = width / 2;
		int cy = height / 2;
		al_draw_rotated_bitmap(current, cx, cy, x + cx, y + cy, rotation_angle, 0);
	}
	else if(specialtyPower[1])  // scared sprite
	{
		al_draw_tinted_bitmap(image[curframe], currentColor, x, y, 0);
	}
	else if(specialtyPower[2])  // baby sprite
	{
		al_draw_scaled_bitmap(image[curframe], 
			0, 0, width, height,  
			x, y, width * scale, height * scale,  
			0);
	}
	else if(specialtyPower[3])  // freeze sprite
	{
		al_draw_bitmap(image[curframe], x, y, 0);
	}
}

void sprite::updatesprite()
{
	// handle freeze sprite special power
	if(specialtyPower[3] && collisionIsTrue)
	{
		freezeSprite();
		// when frozen, only update animation, no movement
		if (framecount++ > framedelay)
		{
			framecount = 0;
			curframe++;
			if (curframe >= maxframe)
				curframe = 0;
		}
		return;
	}
	
	// handle scared sprite lifetime
	if(specialtyPower[1] && live)
	{
		scaredLifetime++;
		if(scaredLifetime >= 900)  
		{
			live = false;
			return;
		}
	}

	// handle spinning sprite lifetime
	if(specialtyPower[0] && live)
	{
		spinningLifetime++;
		if(spinningLifetime >= 900) 
		{
			live = false;
			return;
		}
		
		// update spinning sprite rotation
		rotation_angle += 0.1; 
		if(rotation_angle >= 6.28318) 
			rotation_angle = 0;
	}

	
	if (framecount++ > framedelay)
	{
		framecount = 0;
		curframe++;
		if (curframe >= maxframe)
			curframe = 0;
	}

	
	if (++xcount > xdelay)
	{
		xcount = 0;
		x += xspeed;
	}

	
	if (++ycount > ydelay)
	{
		ycount = 0;
		y += yspeed;
	}
}

void sprite::bouncesprite(int SCREEN_W, int SCREEN_H)
{
	if (!live) return;
	// Keep sprite within screen bounds
	if(x < 0)
	{
		x = 0;
		xspeed = abs(xspeed);  // Move right
	}
	if(x + width > SCREEN_W)
	{
		x = SCREEN_W - width;
		xspeed = -abs(xspeed);  // Move left
	}
	if(y < 0)
	{
		y = 0;
		yspeed = abs(yspeed);  // Move down
	}
	if(y + height > SCREEN_H)
	{
		y = SCREEN_H - height;
		yspeed = -abs(yspeed);  // Move up
	}
}

bool sprite::load_animated_sprite(int size)
{
	char s[80];
	maxframe = size;
	for (int n = 0; n < size; n++)
	{
		sprintf_s(s, "%d.png", n);
		image[n] = al_load_bitmap(s);
		
		if (!image[n])
		{
			for(int i = 0; i < n; i++)
			{
				al_destroy_bitmap(image[i]);
			}
			return false;
		}
		
		al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
	}
	
	width = al_get_bitmap_width(image[0]);
	height = al_get_bitmap_height(image[0]);
	
	curframe = 0;
	framedelay = 8;
	framecount = 0;
	
	return true;
}

sprite::~sprite() {}

void sprite::scaredSprite()
{
	// generate new random color
	unsigned char r = rand() % 256;
	unsigned char g = rand() % 256;
	unsigned char b = rand() % 256;
	currentColor = al_map_rgb(r, g, b);
}

void sprite::babySprite()
{
	scale *= 0.5;  // reduce size by half
	if(scale < 0.1)  // if too small, die
	{
		live = false;
	}
}

void sprite::freezeSprite()
{
	if(specialtyPower[3] && collisionIsTrue)
	{
		double timeSinceCollision = al_get_time() - collisionTime;
		if(timeSinceCollision >= 5.0)
		{
			// kill the sprite so a new one can be created
			live = false;
			return;
		}
	}
}

void sprite::collision(sprite aliens[], int size, int currentIndex, int SCREEN_W, int SCREEN_H)
{
	for(int i = 0; i < size; i++)
	{
		if(i != currentIndex)  // don't check collision with self
		{
			if(x < aliens[i].x + width && x + width > aliens[i].x)  // width collision
			{
				if(y < aliens[i].y + height && y + height > aliens[i].y)  // height collision
				{
					if(specialtyPower[0])  // spinning power 
					{
						// teleport to random location like scared sprite
						x = rand() % (SCREEN_W - width);
						y = rand() % (SCREEN_H - height);
					}
					else if(specialtyPower[3] && !collisionIsTrue)  // freeze power
					{
						collisionIsTrue = true;
						collisionTime = al_get_time();
					}
					else if(specialtyPower[1])  // scared power
					{
						// teleport to random location
						x = rand() % (SCREEN_W - width);
						y = rand() % (SCREEN_H - height);
						scaredSprite();  // change color
					}
					else if(specialtyPower[2])  // baby power
					{
						babySprite();  // reduce size
					}
				}
			}
		}
	}
	
	// if we're frozen, check if it's time to die (only for freeze power)
	if(specialtyPower[3] && collisionIsTrue)
	{
		freezeSprite();
	}
}

void sprite::destroy_images() {
	for (int i = 0; i < 9; i++) {
		if (image[i]) {
			al_destroy_bitmap(image[i]);
			image[i] = nullptr;
		}
	}
}

void sprite::setPower(int power) {
	for(int i = 0; i < 4; i++) 
	specialtyPower[i] = false;
	specialtyPower[power] = true;
	
	if(power == 1) {
		scaredSprite();
	}
}