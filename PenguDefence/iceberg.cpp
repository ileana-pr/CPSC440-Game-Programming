#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "iceberg.h"

iceberg::iceberg()
{
    x = 0;
    y = 0;
    bound_x = 0;
    bound_y = 0;
    live = true;
    speed = 0;
    image = al_load_bitmap("boat.png");
    lives = 3;
}

iceberg::~iceberg()
{
    al_destroy_bitmap(image);
}
void iceberg::draw_iceberg()
{
    al_draw_bitmap(image, x, y, 0);
}

void iceberg::update_iceberg()
{
    x -= speed;
}
void iceberg::removeLife()
{
    lives--;
}

int iceberg::get_lives()
{
    return lives;       
}

void iceberg::start_iceberg(int width, int height)
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




   
