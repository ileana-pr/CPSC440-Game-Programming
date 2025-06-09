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
    image = al_load_bitmap("iceberg.png");
}







   
