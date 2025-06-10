#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "snowball.h"
#include "penguinFiring.h"
#include "penguinDropping.h"

snowball::snowball()
{
    image = al_load_bitmap("snowball.png");
}

