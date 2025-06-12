#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "iceberg.h"

iceberg::iceberg()
{
    x = 0;
    y = 0;
    live = true;
    speed = 0;
    image = al_load_bitmap("boat.png");
    lives = 3;
    if(image) {
        bound_x = al_get_bitmap_width(image);
        bound_y = al_get_bitmap_height(image);
    } else {
        bound_x = 50; 
        bound_y = 50;
    }
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
    // position iceberg at bottom center of screen
    x = width / 2 - bound_x / 2;
    y = height - bound_y - 10;
    live = true;
}

int iceberg::get_x()
{
    return x;
}

int iceberg::get_y() 
{
    return y;
}

int iceberg::get_bound_x()
{
    return al_get_bitmap_width(image);
}

int iceberg::get_bound_y()
{
    return al_get_bitmap_height(image);
}




   
