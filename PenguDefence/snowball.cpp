#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "snowball.h"
#include "penguinFiring.h"
#include "penguinDropping.h"

snowball::snowball()
{
    image = al_load_bitmap("smile.png");
}

snowball::snowball()
{
	speed = 10;
	live = false;
	image = al_load_bitmap("smile.png");
}
snowball::~snowball()
{
	al_destroy_bitmap(image);
}
void snowball::draw_snowball()
{

	if(live)
		al_draw_rotated_bitmap(image,al_get_bitmap_width(image)/2,al_get_bitmap_height(image)/2,x,y,90,0);

}
void snowball::fire_snowball(penguinFiring &penguinFiring)
{
	if(!live)
	{
		x = penguinFiring.get_x();
		y = penguinFiring.get_y();
		live = true;
	}
}
void snowball::update_snowball(int width, int height)
{
	if(live)
	{
		x += speed;
		if(x > width || y > height)
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