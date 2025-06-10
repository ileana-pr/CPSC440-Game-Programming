#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "penguinDropping.h"

penguinDropping::penguinDropping()
{
    image = al_load_bitmap("penguin.png");
    if (!image)
    {
        printf("Failed to load penguin image\n");
        al_destroy_display(display);
        return -1;
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

