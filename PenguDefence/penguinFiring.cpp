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
    image = al_load_bitmap("penguin.png");
    if (!image)
    {
        printf("Failed to load penguin image\n");
    }

    angle = 213;
    score = 0;
}

penguinFiring::~penguinFiring()
{
    al_destroy_bitmap(image);
}

void penguinFiring::start_penguinFiring(int width, int height)
{
    x = width / 2;
    y = height - 50;
    live = true;
}

void penguinFiring::draw_penguinFiring()
{
    if(live)
    {
        float display_angle = (angle - 64.0) / 256.0 * (2 * M_PI);
        al_draw_rotated_bitmap(image, al_get_bitmap_width(image) / 2, al_get_bitmap_height(image) / 2, x, y, display_angle, 0);
    }
}

void penguinFiring::update_penguinFiring()
{
    // any other update logic for the firing penguin
}

void penguinFiring::rotate_left()
{
    angle -= 0.8;
    if (angle < 0)
    {
        angle = 256;
    }
    if (angle < 171 && angle > 85)
    {
        angle = 171;
    }
}

void penguinFiring::rotate_right()
{
    angle += 0.8;
    if (angle > 256)
    {
        angle = 0;
    }
    if (angle < 171 && angle > 85)
    {
        angle = 85;
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
    return al_get_bitmap_width(image);
}

int penguinFiring::get_bound_y()
{
    return al_get_bitmap_height(image);
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

void penguinFiring::collide_penguinFiring(iceberg &iceberg)
{
    // collision logic with iceberg if needed
}











