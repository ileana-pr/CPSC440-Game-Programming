#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "penguinFiring.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

penguinFiring::penguinFiring()
{
    image = al_load_bitmap("happy.png");
    
    angle = 128;
    score = 0;
}

penguinFiring::~penguinFiring()
{
    al_destroy_bitmap(image);
}

void penguinFiring::start_penguinFiring(int width, int height)
{
    x = width / 2;
    y = height - 100;
    live = true;
}

void penguinFiring::draw_penguinFiring()
{
    if(live && image)
    {
        float radian_angle = ((angle + 64.0) / 0.711) * (2 * M_PI / 360.0) + M_PI/2; 
        float scale = 0.1;  
        al_draw_scaled_rotated_bitmap(image, 
                                     al_get_bitmap_width(image) / 2, al_get_bitmap_height(image) / 2, 
                                     x, y, scale, scale, radian_angle, 0);
    }
}

void penguinFiring::update_penguinFiring()
{
    if (x < get_bound_x())
        x = get_bound_x();
    if (x > 640 - get_bound_x())
        x = 640 - get_bound_x();
}

void penguinFiring::rotate_left()
{
    angle -= 2.5;
    if (angle < 95)
    {
        angle = 95;
    }
}

void penguinFiring::rotate_right()
{
    angle += 2.5;
    if (angle > 161)
    {
        angle = 161;
    }
}

float penguinFiring::get_angle()
{
    return angle;
}

int penguinFiring::get_x()
{
    return x;
}

int penguinFiring::get_y()
{
    return y;
}

int penguinFiring::get_bound_x()
{
    return al_get_bitmap_width(image) * 0.1; 
}

int penguinFiring::get_bound_y()
{
    return al_get_bitmap_height(image) * 0.1; 
}

bool penguinFiring::get_live()
{
    return live;
}

void penguinFiring::set_live(bool l)
{
    live = l;
}

int penguinFiring::get_score()
{
    return score;
}

void penguinFiring::add_score()
{
    score++;
}











