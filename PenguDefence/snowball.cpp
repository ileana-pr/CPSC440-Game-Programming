#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <cmath>
#include "snowball.h"
#include "penguinFiring.h"
#include "penguinDropping.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

snowball::snowball()
{
	live = false;
	x = 0;
	y = 0;
	angle = 0;
	image = al_load_bitmap("smile.png");
}

snowball::~snowball()
{
	al_destroy_bitmap(image);
}
void snowball::draw_snowball()
{
	if(live && image)
	{
		float scale = 0.6; 
		al_draw_scaled_rotated_bitmap(image, 
									 al_get_bitmap_width(image)/2, al_get_bitmap_height(image)/2,
									 x, y, scale, scale, 90, 0);
	}
}
void snowball::fire_snowball(penguinFiring &penguinFiring)
{
	if(!live)
	{
		x = penguinFiring.get_x();
		y = penguinFiring.get_y();
		angle = penguinFiring.get_angle();
		live = true;
	}
}
void snowball::update_snowball(int width, int height)
{
	if(live)
	{
		float angle_rad = (angle - 64.0) / 256.0 * (2 * M_PI);
		x += BALL_SPEED * cos(angle_rad);
		y += BALL_SPEED * sin(angle_rad);
		
		if(x > width || x < 0 || y > height || y < 0)
			live = false;
	}
}
void snowball::collide_snowball(penguinDropping pd[], int cSize, penguinFiring &penguinFiring)
{
	if(live)
	{
		for(int j =0; j < cSize; j++)
		{
			if(pd[j].get_live())
			{
				if(x > (pd[j].get_x() - pd[j].get_bound_x()) &&
					x < (pd[j].get_x() + pd[j].get_bound_x()) &&
					y > (pd[j].get_y() - pd[j].get_bound_y()) &&
					y < (pd[j].get_y() + pd[j].get_bound_y()))
				{
					live = false;
					pd[j].set_live(false);
					penguinFiring.add_score();
				}
			}
		}
	}
}

bool snowball::is_live()
{
	return live;
}

int snowball::get_x()
{
	return (int)x;
}

int snowball::get_y()
{
	return (int)y;
}

int snowball::get_bound_x()
{
	return al_get_bitmap_width(image) * 0.6; 
}

int snowball::get_bound_y()
{
	return al_get_bitmap_height(image) * 0.6; 
}

bool snowball::get_live()
{
	return live;
}

void snowball::set_live(bool l)
{
	live = l;
}