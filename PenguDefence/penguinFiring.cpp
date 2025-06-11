#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "penguinFiring.h"

penguinFiring::penguinFiring()
{
    image = al_load_bitmap("happy.png");
    if (!image)
    {
        printf("Failed to load happy image\n");
    }

    x = 0;
    y = 0;
    bound_x = al_get_bitmap_width(image);
    bound_y = al_get_bitmap_height(image);
    speed = 0;
}

penguinFiring::~penguinFiring()
{
    al_destroy_bitmap(image);
}

void penguinFiring::draw_penguinFiring()
{
    al_draw_bitmap(image, x, y, 0);
}


void penguinFiring::add_score()
{
    score++;
}







