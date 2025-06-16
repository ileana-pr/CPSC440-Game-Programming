#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "Sprite.h"

#include <iostream>
using namespace std;

void sprite::drawSprite()
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	
	if(specialtyPower[0]) // spinning
	{
		al_translate_transform(&transform, x + width/2, y + height/2);
		al_rotate_transform(&transform, rotation);
		al_translate_transform(&transform, -(x + width/2), -(y + height/2));
		al_use_transform(&transform);
	}
	
	if(specialtyPower[1] && collisionIsTrue) // scared
	{
		al_draw_tinted_bitmap(image[curframe], currentColor, x, y, 0);
	}
	else if(specialtyPower[2] && collisionIsTrue) // baby
	{
		al_draw_scaled_bitmap(image[curframe], 
			0, 0, width, height,
			x, y, width * scale, height * scale,
			0);
	}
	else if(specialtyPower[3] && collisionIsTrue) // freeze
	{
		al_draw_bitmap(image[curframe], x, y, 0);
	}
	else
	{
		al_draw_bitmap(image[curframe], x, y, 0);
	}
	
	al_identity_transform(&transform);
	al_use_transform(&transform);
}

void sprite::updatesprite()
{
	//update x position
	if (++xcount > xdelay)
	{
		xcount = 0;
		x += xspeed;
	}

	//update y position
	if (++ycount > ydelay)
	{
		ycount = 0;
		y += yspeed;
	}


	if (framecount++ > framedelay)
	{
		framecount = 0;
		curframe++;
		if (curframe >= maxframe)
			curframe = 0;
	}
}

void sprite::bouncesprite(int SCREEN_W, int SCREEN_H)
{
	//simple screen bouncing behavior
	if (x < 0)
	{
		x = 0;
		xspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (x > SCREEN_W - width)
	{
		x = SCREEN_W - width;
		xspeed = rand() % 2 - 6;
		animdir *= -1;
	}

	if (y < 0)
	{
		y = 0;
		yspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (y > SCREEN_H - height)
	{
		y = SCREEN_H -  height;
		yspeed = rand() % 2 - 6;
		animdir *= -1;
	}

}

void sprite::load_animated_sprite(int size)
{
	//load the animated sprite
	char s[80];
	maxframe=size;
	for (int n=0; n<size; n++)
	{
		sprintf_s(s,"%d.png",n);
		image[n] = al_load_bitmap(s);

		al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
	}  
	width=al_get_bitmap_width(image[0]);
	height=al_get_bitmap_height(image[0]);
	curframe = 0;
	framedelay = 5;
	framecount = 0;


}

sprite::~sprite()
{
	for(int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}

void sprite::scaredSprite()
{
	
}

void sprite::babySprite()
{

}

void sprite::spinningSprite() 
{

}

void sprite::freezeSprite()
{

}