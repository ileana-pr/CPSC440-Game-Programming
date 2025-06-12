#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include "penguinDropping.h"
#include "penguinFiring.h"
#include "iceberg.h"

penguinDropping::penguinDropping()
{
    image = al_load_bitmap("mad.png");
    if (!image)
    {
        printf("Failed to load mad image\n");
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

int penguinDropping::get_x()
{
    return x;
}

int penguinDropping::get_y()
{
    return y;
}

int penguinDropping::get_bound_x()
{
    return bound_x;
}

int penguinDropping::get_bound_y()
{
    return bound_y;
}

bool penguinDropping::get_live()
{
    return live;
}

void penguinDropping::set_live(bool l)
{
    live = l;
}
