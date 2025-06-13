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
   

    live = false;
    landed = false;
    speed = 2; 
    bound_x = 32; 
    bound_y = 32;
    x = 0;
    y = 0;
}

penguinDropping::~penguinDropping()
{
    al_destroy_bitmap(image);
}

void penguinDropping::draw_penguinDropping()
{
    if((live || landed) && image) {
        float scale = 0.1; 
        al_draw_scaled_rotated_bitmap(image, 
                                    al_get_bitmap_width(image)/2, al_get_bitmap_height(image)/2,
                                    x, y, scale, scale, 0, 0);
    }
}

void penguinDropping::start_penguinDropping(int width, int height, iceberg &iceberg)
{
    if(!live)
    {
        if(rand() % 180 == 0)  
        {
            live = true;
            landed = false;
            
            int iceberg_x = iceberg.get_x();
            int iceberg_width = iceberg.get_bound_x();
            x = iceberg_x + bound_x + (rand() % (iceberg_width - 2 * bound_x));
            y = -50;
        }
    }
}

void penguinDropping::update_penguinDropping(iceberg &iceberg)
{
    if(live && !landed)
    {
        y += speed;
        
        if(y > 420)
        {
            y = 420;  
            landed = true;
            live = false;  
            iceberg.removeLife();  
        }
    }
    
    if(landed && iceberg.get_lives() <= 0)
    {
        y += 1;  
        if(y > 600)  
        {
            landed = false;
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
