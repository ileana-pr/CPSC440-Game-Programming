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
    lives = 10;
    is_sinking = false;
    sink_speed = 1;
    sink_angle = 0;
    
    image = al_load_bitmap("boat.png");
    if (image) {
        scaled_width = al_get_bitmap_width(image) * SCALE_FACTOR;
        scaled_height = al_get_bitmap_height(image) * SCALE_FACTOR;
    }
    
    bound_x = scaled_width;
    bound_y = scaled_height;
}

iceberg::~iceberg()
{
    al_destroy_bitmap(image);
}

void iceberg::draw_iceberg()
{
    if(live) {
        if(image) {
            if(is_sinking) {
                al_draw_scaled_rotated_bitmap(image, 
                    al_get_bitmap_width(image)/2, al_get_bitmap_height(image)/2,
                    x + scaled_width/2, y + scaled_height/2, 
                    SCALE_FACTOR, SCALE_FACTOR, 
                    sink_angle, 0);
            } else {
                al_draw_scaled_bitmap(image, 0, 0, 
                    al_get_bitmap_width(image), al_get_bitmap_height(image), 
                    x, y, scaled_width, scaled_height, 0);
            }
        }
        
        if(!is_sinking) {
            for(int i = 0; i < lives; i++) {
                al_draw_filled_circle(600 - (i * 20), 20, 8, al_map_rgb(255, 0, 0));
            }
        }
    }
}

void iceberg::update_iceberg()
{
    if(is_sinking) {
        
        y += sink_speed;
        sink_angle += 0.02;
        sink_speed += 0.1;
        
        
        if(y > 600) {
            live = false;
        }
    }
}

void iceberg::removeLife()
{
    lives--;
    if(lives <= 0 && !is_sinking) {
        al_rest(2.0);  
        is_sinking = true;
        sink_speed = 1;
        sink_angle = 0;
    }
}

int iceberg::get_lives()
{
    return lives;       
}

void iceberg::start_iceberg(int width, int height)
{
    if (image) {
        x = (width - scaled_width) / 2; 
        y = height - scaled_height + 50;  
    } else {
        x = width / 2 - 50;  
        y = height - 50;  
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




   
