#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
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
        scaled_width = al_get_bitmap_width(image) * SCALE_FACTOR;
        scaled_height = al_get_bitmap_height(image) * SCALE_FACTOR;
        bound_x = scaled_width;
        bound_y = scaled_height;
        
    } else {
        scaled_width = 30;  
        scaled_height = 30;
        bound_x = scaled_width;
        bound_y = scaled_height;
    }
}

iceberg::~iceberg()
{
    al_destroy_bitmap(image);
}
void iceberg::draw_iceberg()
{
    if(image && live) {
       
        al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 
                             x, y, scaled_width, scaled_height, 0);
    }
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
    if (image) {
        x = (width - scaled_width) / 2; 
        y = height - scaled_height+80;
    } else {
        x = width / 2 - 50;  
        y = height - 30;    
    }
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
    return scaled_width;
}

int iceberg::get_bound_y()
{
    return scaled_height;
}




   
