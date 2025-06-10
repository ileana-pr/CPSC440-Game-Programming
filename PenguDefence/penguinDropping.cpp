#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include "penguinDropping.h"
#include "penguinFiring.h"
#include "iceberg.h"

penguinDropping::penguinDropping()
{
    image = al_load_bitmap("penguin.png");
    if (!image)
    {
        printf("Failed to load penguin image\n");
        return;
    }

    live = false;
    speed = 5; 
    bound_x = al_get_bitmap_width(image);
    bound_y = al_get_bitmap_height(image);
    x = 0;
    y = 0;
}

penguinDropping::~penguinDropping()
{
    al_destroy_bitmap(image);
}

void penguinDropping::draw_penguinDropping()
{
    al_draw_bitmap(image, x, y, 0);
}

void penguinDropping::start_penguinDropping(int width, int height)
{
    if(!live)
	{
		if(rand() % 500 == 0)
		{
			live = true;
			x = width;
			y = rand() % (height-bound_y);

		}
	}
}

void penguinDropping::update_penguinDropping()
{

	if(live)
	{
		x -= speed;
	}

}
void penguinDropping::collide_penguinDropping(iceberg &iceberg)
{
	if(live)
	{
		if( x - bound_x < iceberg.get_x() + iceberg.get_bound_x() &&
			x + bound_x > iceberg.get_x() - iceberg.get_bound_x() &&
			y - bound_y < iceberg.get_y() + iceberg.get_bound_y() &&
			y + bound_y > iceberg.get_y() - iceberg.get_bound_y())
		{
			iceberg.removeLife();
			live = false;
		}
		else if(x < 0)
		{
			live = false;
		}
	}
}
